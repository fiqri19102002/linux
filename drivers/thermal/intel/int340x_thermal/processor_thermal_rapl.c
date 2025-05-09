// SPDX-License-Identifier: GPL-2.0-only
/*
 * processor thermal device RFIM control
 * Copyright (c) 2020, Intel Corporation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include "processor_thermal_device.h"

static struct rapl_if_priv rapl_mmio_priv;

static const struct rapl_mmio_regs rapl_mmio_default = {
	.reg_unit = 0x5938,
	.regs[RAPL_DOMAIN_PACKAGE] = { 0x59a0, 0x593c, 0x58f0, 0, 0x5930, 0x59b0},
	.regs[RAPL_DOMAIN_DRAM] = { 0x58e0, 0x58e8, 0x58ec, 0, 0},
	.limits[RAPL_DOMAIN_PACKAGE] = BIT(POWER_LIMIT2) | BIT(POWER_LIMIT4),
	.limits[RAPL_DOMAIN_DRAM] = BIT(POWER_LIMIT2),
};

static int rapl_mmio_read_raw(int cpu, struct reg_action *ra)
{
	if (!ra->reg.mmio)
		return -EINVAL;

	ra->value = readq(ra->reg.mmio);
	ra->value &= ra->mask;
	return 0;
}

static int rapl_mmio_write_raw(int cpu, struct reg_action *ra)
{
	u64 val;

	if (!ra->reg.mmio)
		return -EINVAL;

	val = readq(ra->reg.mmio);
	val &= ~ra->mask;
	val |= ra->value;
	writeq(val, ra->reg.mmio);
	return 0;
}

int proc_thermal_rapl_add(struct pci_dev *pdev, struct proc_thermal_device *proc_priv)
{
	const struct rapl_mmio_regs *rapl_regs = &rapl_mmio_default;
	struct rapl_package *rp;
	enum rapl_domain_reg_id reg;
	enum rapl_domain_type domain;
	int ret;

	if (!rapl_regs)
		return 0;

	for (domain = RAPL_DOMAIN_PACKAGE; domain < RAPL_DOMAIN_MAX; domain++) {
		for (reg = RAPL_DOMAIN_REG_LIMIT; reg < RAPL_DOMAIN_REG_MAX; reg++)
			if (rapl_regs->regs[domain][reg])
				rapl_mmio_priv.regs[domain][reg].mmio =
						proc_priv->mmio_base +
						rapl_regs->regs[domain][reg];
		rapl_mmio_priv.limits[domain] = rapl_regs->limits[domain];
	}
	rapl_mmio_priv.type = RAPL_IF_MMIO;
	rapl_mmio_priv.reg_unit.mmio = proc_priv->mmio_base + rapl_regs->reg_unit;

	rapl_mmio_priv.read_raw = rapl_mmio_read_raw;
	rapl_mmio_priv.write_raw = rapl_mmio_write_raw;

	rapl_mmio_priv.control_type = powercap_register_control_type(NULL, "intel-rapl-mmio", NULL);
	if (IS_ERR(rapl_mmio_priv.control_type)) {
		pr_debug("failed to register powercap control_type.\n");
		return PTR_ERR(rapl_mmio_priv.control_type);
	}

	/* Register a RAPL package device for package 0 which is always online */
	rp = rapl_find_package_domain(0, &rapl_mmio_priv, false);
	if (rp) {
		ret = -EEXIST;
		goto err;
	}

	rp = rapl_add_package(0, &rapl_mmio_priv, false);
	if (IS_ERR(rp)) {
		ret = PTR_ERR(rp);
		goto err;
	}

	return 0;

err:
	powercap_unregister_control_type(rapl_mmio_priv.control_type);
	rapl_mmio_priv.control_type = NULL;
	return ret;
}
EXPORT_SYMBOL_GPL(proc_thermal_rapl_add);

void proc_thermal_rapl_remove(void)
{
	struct rapl_package *rp;

	if (IS_ERR_OR_NULL(rapl_mmio_priv.control_type))
		return;

	rp = rapl_find_package_domain(0, &rapl_mmio_priv, false);
	if (rp)
		rapl_remove_package(rp);
	powercap_unregister_control_type(rapl_mmio_priv.control_type);
}
EXPORT_SYMBOL_GPL(proc_thermal_rapl_remove);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("RAPL interface using MMIO");
