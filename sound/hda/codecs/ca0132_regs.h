/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * HD audio codec driver for Creative CA0132 chip.
 * CA0132 registers defines.
 *
 * Copyright (c) 2011, Creative Technology Ltd.
 */

#ifndef __CA0132_REGS_H
#define __CA0132_REGS_H

#define DSP_CHIP_OFFSET                0x100000
#define DSP_DBGCNTL_MODULE_OFFSET      0xE30
#define DSP_DBGCNTL_INST_OFFSET \
	(DSP_CHIP_OFFSET + DSP_DBGCNTL_MODULE_OFFSET)

#define DSP_DBGCNTL_EXEC_LOBIT         0x0
#define DSP_DBGCNTL_EXEC_HIBIT         0x3
#define DSP_DBGCNTL_EXEC_MASK          0xF

#define DSP_DBGCNTL_SS_LOBIT           0x4
#define DSP_DBGCNTL_SS_HIBIT           0x7
#define DSP_DBGCNTL_SS_MASK            0xF0

#define DSP_DBGCNTL_STATE_LOBIT        0xA
#define DSP_DBGCNTL_STATE_HIBIT        0xD
#define DSP_DBGCNTL_STATE_MASK         0x3C00

#define XRAM_CHIP_OFFSET               0x0
#define XRAM_XRAM_CHANNEL_COUNT        0xE000
#define XRAM_XRAM_MODULE_OFFSET        0x0
#define XRAM_XRAM_CHAN_INCR            4
#define XRAM_XRAM_INST_OFFSET(_chan) \
	(XRAM_CHIP_OFFSET + XRAM_XRAM_MODULE_OFFSET + \
	(_chan * XRAM_XRAM_CHAN_INCR))

#define YRAM_CHIP_OFFSET               0x40000
#define YRAM_YRAM_CHANNEL_COUNT        0x8000
#define YRAM_YRAM_MODULE_OFFSET        0x0
#define YRAM_YRAM_CHAN_INCR            4
#define YRAM_YRAM_INST_OFFSET(_chan) \
	(YRAM_CHIP_OFFSET + YRAM_YRAM_MODULE_OFFSET + \
	(_chan * YRAM_YRAM_CHAN_INCR))

#define UC_CHIP_OFFSET                 0x80000
#define UC_UC_CHANNEL_COUNT            0x10000
#define UC_UC_MODULE_OFFSET            0x0
#define UC_UC_CHAN_INCR                4
#define UC_UC_INST_OFFSET(_chan) \
	(UC_CHIP_OFFSET + UC_UC_MODULE_OFFSET + \
	(_chan * UC_UC_CHAN_INCR))

#define AXRAM_CHIP_OFFSET              0x3C000
#define AXRAM_AXRAM_CHANNEL_COUNT      0x1000
#define AXRAM_AXRAM_MODULE_OFFSET      0x0
#define AXRAM_AXRAM_CHAN_INCR          4
#define AXRAM_AXRAM_INST_OFFSET(_chan) \
	(AXRAM_CHIP_OFFSET + AXRAM_AXRAM_MODULE_OFFSET + \
	(_chan * AXRAM_AXRAM_CHAN_INCR))

#define AYRAM_CHIP_OFFSET              0x78000
#define AYRAM_AYRAM_CHANNEL_COUNT      0x1000
#define AYRAM_AYRAM_MODULE_OFFSET      0x0
#define AYRAM_AYRAM_CHAN_INCR          4
#define AYRAM_AYRAM_INST_OFFSET(_chan) \
	(AYRAM_CHIP_OFFSET + AYRAM_AYRAM_MODULE_OFFSET + \
	(_chan * AYRAM_AYRAM_CHAN_INCR))

#define DSPDMAC_CHIP_OFFSET            0x110000
#define DSPDMAC_DMA_CFG_CHANNEL_COUNT  12
#define DSPDMAC_DMACFG_MODULE_OFFSET   0xF00
#define DSPDMAC_DMACFG_CHAN_INCR       0x10
#define DSPDMAC_DMACFG_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_DMACFG_MODULE_OFFSET + \
	(_chan * DSPDMAC_DMACFG_CHAN_INCR))

#define DSPDMAC_DMACFG_DBADR_LOBIT     0x0
#define DSPDMAC_DMACFG_DBADR_HIBIT     0x10
#define DSPDMAC_DMACFG_DBADR_MASK      0x1FFFF
#define DSPDMAC_DMACFG_LP_LOBIT        0x11
#define DSPDMAC_DMACFG_LP_HIBIT        0x11
#define DSPDMAC_DMACFG_LP_MASK         0x20000

#define DSPDMAC_DMACFG_AINCR_LOBIT     0x12
#define DSPDMAC_DMACFG_AINCR_HIBIT     0x12
#define DSPDMAC_DMACFG_AINCR_MASK      0x40000

#define DSPDMAC_DMACFG_DWR_LOBIT       0x13
#define DSPDMAC_DMACFG_DWR_HIBIT       0x13
#define DSPDMAC_DMACFG_DWR_MASK        0x80000

#define DSPDMAC_DMACFG_AJUMP_LOBIT     0x14
#define DSPDMAC_DMACFG_AJUMP_HIBIT     0x17
#define DSPDMAC_DMACFG_AJUMP_MASK      0xF00000

#define DSPDMAC_DMACFG_AMODE_LOBIT     0x18
#define DSPDMAC_DMACFG_AMODE_HIBIT     0x19
#define DSPDMAC_DMACFG_AMODE_MASK      0x3000000

#define DSPDMAC_DMACFG_LK_LOBIT        0x1A
#define DSPDMAC_DMACFG_LK_HIBIT        0x1A
#define DSPDMAC_DMACFG_LK_MASK         0x4000000

#define DSPDMAC_DMACFG_AICS_LOBIT      0x1B
#define DSPDMAC_DMACFG_AICS_HIBIT      0x1F
#define DSPDMAC_DMACFG_AICS_MASK       0xF8000000

#define DSPDMAC_DMACFG_LP_SINGLE                 0
#define DSPDMAC_DMACFG_LP_LOOPING                1

#define DSPDMAC_DMACFG_AINCR_XANDY               0
#define DSPDMAC_DMACFG_AINCR_XORY                1

#define DSPDMAC_DMACFG_DWR_DMA_RD                0
#define DSPDMAC_DMACFG_DWR_DMA_WR                1

#define DSPDMAC_DMACFG_AMODE_LINEAR              0
#define DSPDMAC_DMACFG_AMODE_RSV1                1
#define DSPDMAC_DMACFG_AMODE_WINTLV              2
#define DSPDMAC_DMACFG_AMODE_GINTLV              3

#define DSPDMAC_DSP_ADR_OFS_CHANNEL_COUNT 12
#define DSPDMAC_DSPADROFS_MODULE_OFFSET 0xF04
#define DSPDMAC_DSPADROFS_CHAN_INCR    0x10
#define DSPDMAC_DSPADROFS_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_DSPADROFS_MODULE_OFFSET + \
	(_chan * DSPDMAC_DSPADROFS_CHAN_INCR))

#define DSPDMAC_DSPADROFS_COFS_LOBIT   0x0
#define DSPDMAC_DSPADROFS_COFS_HIBIT   0xF
#define DSPDMAC_DSPADROFS_COFS_MASK    0xFFFF

#define DSPDMAC_DSPADROFS_BOFS_LOBIT   0x10
#define DSPDMAC_DSPADROFS_BOFS_HIBIT   0x1F
#define DSPDMAC_DSPADROFS_BOFS_MASK    0xFFFF0000

#define DSPDMAC_DSP_ADR_WOFS_CHANNEL_COUNT 12
#define DSPDMAC_DSPADRWOFS_MODULE_OFFSET 0xF04
#define DSPDMAC_DSPADRWOFS_CHAN_INCR   0x10

#define DSPDMAC_DSPADRWOFS_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_DSPADRWOFS_MODULE_OFFSET + \
	(_chan * DSPDMAC_DSPADRWOFS_CHAN_INCR))

#define DSPDMAC_DSPADRWOFS_WCOFS_LOBIT 0x0
#define DSPDMAC_DSPADRWOFS_WCOFS_HIBIT 0xA
#define DSPDMAC_DSPADRWOFS_WCOFS_MASK  0x7FF

#define DSPDMAC_DSPADRWOFS_WCBFR_LOBIT 0xB
#define DSPDMAC_DSPADRWOFS_WCBFR_HIBIT 0xF
#define DSPDMAC_DSPADRWOFS_WCBFR_MASK  0xF800

#define DSPDMAC_DSPADRWOFS_WBOFS_LOBIT 0x10
#define DSPDMAC_DSPADRWOFS_WBOFS_HIBIT 0x1A
#define DSPDMAC_DSPADRWOFS_WBOFS_MASK  0x7FF0000

#define DSPDMAC_DSPADRWOFS_WBBFR_LOBIT 0x1B
#define DSPDMAC_DSPADRWOFS_WBBFR_HIBIT 0x1F
#define DSPDMAC_DSPADRWOFS_WBBFR_MASK  0xF8000000

#define DSPDMAC_DSP_ADR_GOFS_CHANNEL_COUNT 12
#define DSPDMAC_DSPADRGOFS_MODULE_OFFSET 0xF04
#define DSPDMAC_DSPADRGOFS_CHAN_INCR   0x10
#define DSPDMAC_DSPADRGOFS_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_DSPADRGOFS_MODULE_OFFSET + \
	(_chan * DSPDMAC_DSPADRGOFS_CHAN_INCR))

#define DSPDMAC_DSPADRGOFS_GCOFS_LOBIT 0x0
#define DSPDMAC_DSPADRGOFS_GCOFS_HIBIT 0x9
#define DSPDMAC_DSPADRGOFS_GCOFS_MASK  0x3FF

#define DSPDMAC_DSPADRGOFS_GCS_LOBIT   0xA
#define DSPDMAC_DSPADRGOFS_GCS_HIBIT   0xC
#define DSPDMAC_DSPADRGOFS_GCS_MASK    0x1C00

#define DSPDMAC_DSPADRGOFS_GCBFR_LOBIT 0xD
#define DSPDMAC_DSPADRGOFS_GCBFR_HIBIT 0xF
#define DSPDMAC_DSPADRGOFS_GCBFR_MASK  0xE000

#define DSPDMAC_DSPADRGOFS_GBOFS_LOBIT 0x10
#define DSPDMAC_DSPADRGOFS_GBOFS_HIBIT 0x19
#define DSPDMAC_DSPADRGOFS_GBOFS_MASK  0x3FF0000

#define DSPDMAC_DSPADRGOFS_GBS_LOBIT   0x1A
#define DSPDMAC_DSPADRGOFS_GBS_HIBIT   0x1C
#define DSPDMAC_DSPADRGOFS_GBS_MASK    0x1C000000

#define DSPDMAC_DSPADRGOFS_GBBFR_LOBIT 0x1D
#define DSPDMAC_DSPADRGOFS_GBBFR_HIBIT 0x1F
#define DSPDMAC_DSPADRGOFS_GBBFR_MASK  0xE0000000

#define DSPDMAC_XFR_CNT_CHANNEL_COUNT  12
#define DSPDMAC_XFRCNT_MODULE_OFFSET   0xF08
#define DSPDMAC_XFRCNT_CHAN_INCR       0x10

#define DSPDMAC_XFRCNT_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_XFRCNT_MODULE_OFFSET + \
	(_chan * DSPDMAC_XFRCNT_CHAN_INCR))

#define DSPDMAC_XFRCNT_CCNT_LOBIT      0x0
#define DSPDMAC_XFRCNT_CCNT_HIBIT      0xF
#define DSPDMAC_XFRCNT_CCNT_MASK       0xFFFF

#define DSPDMAC_XFRCNT_BCNT_LOBIT      0x10
#define DSPDMAC_XFRCNT_BCNT_HIBIT      0x1F
#define DSPDMAC_XFRCNT_BCNT_MASK       0xFFFF0000

#define DSPDMAC_IRQ_CNT_CHANNEL_COUNT  12
#define DSPDMAC_IRQCNT_MODULE_OFFSET   0xF0C
#define DSPDMAC_IRQCNT_CHAN_INCR       0x10
#define DSPDMAC_IRQCNT_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_IRQCNT_MODULE_OFFSET + \
	(_chan * DSPDMAC_IRQCNT_CHAN_INCR))

#define DSPDMAC_IRQCNT_CICNT_LOBIT     0x0
#define DSPDMAC_IRQCNT_CICNT_HIBIT     0xF
#define DSPDMAC_IRQCNT_CICNT_MASK      0xFFFF

#define DSPDMAC_IRQCNT_BICNT_LOBIT     0x10
#define DSPDMAC_IRQCNT_BICNT_HIBIT     0x1F
#define DSPDMAC_IRQCNT_BICNT_MASK      0xFFFF0000

#define DSPDMAC_AUD_CHSEL_CHANNEL_COUNT 12
#define DSPDMAC_AUDCHSEL_MODULE_OFFSET 0xFC0
#define DSPDMAC_AUDCHSEL_CHAN_INCR     0x4
#define DSPDMAC_AUDCHSEL_INST_OFFSET(_chan) \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_AUDCHSEL_MODULE_OFFSET + \
	(_chan * DSPDMAC_AUDCHSEL_CHAN_INCR))

#define DSPDMAC_AUDCHSEL_ACS_LOBIT     0x0
#define DSPDMAC_AUDCHSEL_ACS_HIBIT     0x1F
#define DSPDMAC_AUDCHSEL_ACS_MASK      0xFFFFFFFF

#define DSPDMAC_CHNLSTART_MODULE_OFFSET 0xFF0
#define DSPDMAC_CHNLSTART_INST_OFFSET \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_CHNLSTART_MODULE_OFFSET)

#define DSPDMAC_CHNLSTART_EN_LOBIT     0x0
#define DSPDMAC_CHNLSTART_EN_HIBIT     0xB
#define DSPDMAC_CHNLSTART_EN_MASK      0xFFF

#define DSPDMAC_CHNLSTART_VAI1_LOBIT   0xC
#define DSPDMAC_CHNLSTART_VAI1_HIBIT   0xF
#define DSPDMAC_CHNLSTART_VAI1_MASK    0xF000

#define DSPDMAC_CHNLSTART_DIS_LOBIT    0x10
#define DSPDMAC_CHNLSTART_DIS_HIBIT    0x1B
#define DSPDMAC_CHNLSTART_DIS_MASK     0xFFF0000

#define DSPDMAC_CHNLSTART_VAI2_LOBIT   0x1C
#define DSPDMAC_CHNLSTART_VAI2_HIBIT   0x1F
#define DSPDMAC_CHNLSTART_VAI2_MASK    0xF0000000

#define DSPDMAC_CHNLSTATUS_MODULE_OFFSET 0xFF4
#define DSPDMAC_CHNLSTATUS_INST_OFFSET \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_CHNLSTATUS_MODULE_OFFSET)

#define DSPDMAC_CHNLSTATUS_ISC_LOBIT   0x0
#define DSPDMAC_CHNLSTATUS_ISC_HIBIT   0xB
#define DSPDMAC_CHNLSTATUS_ISC_MASK    0xFFF

#define DSPDMAC_CHNLSTATUS_AOO_LOBIT   0xC
#define DSPDMAC_CHNLSTATUS_AOO_HIBIT   0xC
#define DSPDMAC_CHNLSTATUS_AOO_MASK    0x1000

#define DSPDMAC_CHNLSTATUS_AOU_LOBIT   0xD
#define DSPDMAC_CHNLSTATUS_AOU_HIBIT   0xD
#define DSPDMAC_CHNLSTATUS_AOU_MASK    0x2000

#define DSPDMAC_CHNLSTATUS_AIO_LOBIT   0xE
#define DSPDMAC_CHNLSTATUS_AIO_HIBIT   0xE
#define DSPDMAC_CHNLSTATUS_AIO_MASK    0x4000

#define DSPDMAC_CHNLSTATUS_AIU_LOBIT   0xF
#define DSPDMAC_CHNLSTATUS_AIU_HIBIT   0xF
#define DSPDMAC_CHNLSTATUS_AIU_MASK    0x8000

#define DSPDMAC_CHNLSTATUS_IEN_LOBIT   0x10
#define DSPDMAC_CHNLSTATUS_IEN_HIBIT   0x1B
#define DSPDMAC_CHNLSTATUS_IEN_MASK    0xFFF0000

#define DSPDMAC_CHNLSTATUS_VAI0_LOBIT  0x1C
#define DSPDMAC_CHNLSTATUS_VAI0_HIBIT  0x1F
#define DSPDMAC_CHNLSTATUS_VAI0_MASK   0xF0000000

#define DSPDMAC_CHNLPROP_MODULE_OFFSET 0xFF8
#define DSPDMAC_CHNLPROP_INST_OFFSET \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_CHNLPROP_MODULE_OFFSET)

#define DSPDMAC_CHNLPROP_DCON_LOBIT    0x0
#define DSPDMAC_CHNLPROP_DCON_HIBIT    0xB
#define DSPDMAC_CHNLPROP_DCON_MASK     0xFFF

#define DSPDMAC_CHNLPROP_FFS_LOBIT     0xC
#define DSPDMAC_CHNLPROP_FFS_HIBIT     0xC
#define DSPDMAC_CHNLPROP_FFS_MASK      0x1000

#define DSPDMAC_CHNLPROP_NAJ_LOBIT     0xD
#define DSPDMAC_CHNLPROP_NAJ_HIBIT     0xD
#define DSPDMAC_CHNLPROP_NAJ_MASK      0x2000

#define DSPDMAC_CHNLPROP_ENH_LOBIT     0xE
#define DSPDMAC_CHNLPROP_ENH_HIBIT     0xE
#define DSPDMAC_CHNLPROP_ENH_MASK      0x4000

#define DSPDMAC_CHNLPROP_MSPCE_LOBIT   0x10
#define DSPDMAC_CHNLPROP_MSPCE_HIBIT   0x1B
#define DSPDMAC_CHNLPROP_MSPCE_MASK    0xFFF0000

#define DSPDMAC_CHNLPROP_AC_LOBIT      0x1C
#define DSPDMAC_CHNLPROP_AC_HIBIT      0x1F
#define DSPDMAC_CHNLPROP_AC_MASK       0xF0000000

#define DSPDMAC_ACTIVE_MODULE_OFFSET   0xFFC
#define DSPDMAC_ACTIVE_INST_OFFSET \
	(DSPDMAC_CHIP_OFFSET + DSPDMAC_ACTIVE_MODULE_OFFSET)

#define DSPDMAC_ACTIVE_AAR_LOBIT       0x0
#define DSPDMAC_ACTIVE_AAR_HIBIT       0xB
#define DSPDMAC_ACTIVE_AAR_MASK        0xFFF

#define DSPDMAC_ACTIVE_WFR_LOBIT       0xC
#define DSPDMAC_ACTIVE_WFR_HIBIT       0x17
#define DSPDMAC_ACTIVE_WFR_MASK        0xFFF000

#define DSP_AUX_MEM_BASE            0xE000
#define INVALID_CHIP_ADDRESS        (~0U)

#define X_SIZE  (XRAM_XRAM_CHANNEL_COUNT   * XRAM_XRAM_CHAN_INCR)
#define Y_SIZE  (YRAM_YRAM_CHANNEL_COUNT   * YRAM_YRAM_CHAN_INCR)
#define AX_SIZE (AXRAM_AXRAM_CHANNEL_COUNT * AXRAM_AXRAM_CHAN_INCR)
#define AY_SIZE (AYRAM_AYRAM_CHANNEL_COUNT * AYRAM_AYRAM_CHAN_INCR)
#define UC_SIZE (UC_UC_CHANNEL_COUNT       * UC_UC_CHAN_INCR)

#define XEXT_SIZE (X_SIZE + AX_SIZE)
#define YEXT_SIZE (Y_SIZE + AY_SIZE)

#define U64K 0x10000UL

#define X_END  (XRAM_CHIP_OFFSET  + X_SIZE)
#define X_EXT  (XRAM_CHIP_OFFSET  + XEXT_SIZE)
#define AX_END (XRAM_CHIP_OFFSET  + U64K*4)

#define Y_END  (YRAM_CHIP_OFFSET  + Y_SIZE)
#define Y_EXT  (YRAM_CHIP_OFFSET  + YEXT_SIZE)
#define AY_END (YRAM_CHIP_OFFSET  + U64K*4)

#define UC_END (UC_CHIP_OFFSET    + UC_SIZE)

#define X_RANGE_MAIN(a, s) \
	(((a)+((s)-1)*XRAM_XRAM_CHAN_INCR <  X_END))
#define X_RANGE_AUX(a, s)  \
	(((a) >= X_END) && ((a)+((s)-1)*XRAM_XRAM_CHAN_INCR < AX_END))
#define X_RANGE_EXT(a, s)  \
	(((a)+((s)-1)*XRAM_XRAM_CHAN_INCR <  X_EXT))
#define X_RANGE_ALL(a, s)  \
	(((a)+((s)-1)*XRAM_XRAM_CHAN_INCR < AX_END))

#define Y_RANGE_MAIN(a, s) \
	(((a) >= YRAM_CHIP_OFFSET) && \
	((a)+((s)-1)*YRAM_YRAM_CHAN_INCR <  Y_END))
#define Y_RANGE_AUX(a, s)  \
	(((a) >= Y_END) && \
	((a)+((s)-1)*YRAM_YRAM_CHAN_INCR < AY_END))
#define Y_RANGE_EXT(a, s)  \
	(((a) >= YRAM_CHIP_OFFSET) && \
	((a)+((s)-1)*YRAM_YRAM_CHAN_INCR <  Y_EXT))
#define Y_RANGE_ALL(a, s)  \
	(((a) >= YRAM_CHIP_OFFSET) && \
	((a)+((s)-1)*YRAM_YRAM_CHAN_INCR < AY_END))

#define UC_RANGE(a, s) \
	(((a) >= UC_CHIP_OFFSET) && \
	((a)+((s)-1)*UC_UC_CHAN_INCR     < UC_END))

#define X_OFF(a) \
	(((a) - XRAM_CHIP_OFFSET) / XRAM_XRAM_CHAN_INCR)
#define AX_OFF(a) \
	(((a) % (AXRAM_AXRAM_CHANNEL_COUNT * \
	AXRAM_AXRAM_CHAN_INCR)) / AXRAM_AXRAM_CHAN_INCR)

#define Y_OFF(a) \
	(((a) - YRAM_CHIP_OFFSET) / YRAM_YRAM_CHAN_INCR)
#define AY_OFF(a) \
	(((a) % (AYRAM_AYRAM_CHANNEL_COUNT * \
	AYRAM_AYRAM_CHAN_INCR)) / AYRAM_AYRAM_CHAN_INCR)

#define UC_OFF(a)  (((a) - UC_CHIP_OFFSET) / UC_UC_CHAN_INCR)

#define X_EXT_MAIN_SIZE(a)  (XRAM_XRAM_CHANNEL_COUNT - X_OFF(a))
#define X_EXT_AUX_SIZE(a, s) ((s) - X_EXT_MAIN_SIZE(a))

#define Y_EXT_MAIN_SIZE(a)  (YRAM_YRAM_CHANNEL_COUNT - Y_OFF(a))
#define Y_EXT_AUX_SIZE(a, s) ((s) - Y_EXT_MAIN_SIZE(a))

#endif
