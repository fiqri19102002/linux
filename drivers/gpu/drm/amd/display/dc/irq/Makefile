#
# Copyright 2017 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
#
# Makefile for the 'audio' sub-component of DAL.
# It provides the control and status of HW adapter resources,
# that are global for the ASIC and sharable between pipes.

IRQ = irq_service.o

AMD_DAL_IRQ = $(addprefix $(AMDDALPATH)/dc/irq/,$(IRQ))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ)

###############################################################################
# DCE 6x
###############################################################################
ifdef CONFIG_DRM_AMD_DC_SI
IRQ_DCE60 = irq_service_dce60.o

AMD_DAL_IRQ_DCE60 = $(addprefix $(AMDDALPATH)/dc/irq/dce60/,$(IRQ_DCE60))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCE60)
endif

###############################################################################
# DCE 8x
###############################################################################
IRQ_DCE80 = irq_service_dce80.o

AMD_DAL_IRQ_DCE80 = $(addprefix $(AMDDALPATH)/dc/irq/dce80/,$(IRQ_DCE80))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCE80)

###############################################################################
# DCE 11x
###############################################################################
IRQ_DCE11 = irq_service_dce110.o

AMD_DAL_IRQ_DCE11 = $(addprefix $(AMDDALPATH)/dc/irq/dce110/,$(IRQ_DCE11))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCE11)

###############################################################################
# DCE 12x
###############################################################################
IRQ_DCE12 = irq_service_dce120.o

AMD_DAL_IRQ_DCE12 = $(addprefix $(AMDDALPATH)/dc/irq/dce120/,$(IRQ_DCE12))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCE12)

###############################################################################
# DCN 1x
###############################################################################
IRQ_DCN1 = irq_service_dcn10.o

AMD_DAL_IRQ_DCN1 = $(addprefix $(AMDDALPATH)/dc/irq/dcn10/,$(IRQ_DCN1))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN1)
###############################################################################
# DCN 20
###############################################################################
IRQ_DCN2 = irq_service_dcn20.o

AMD_DAL_IRQ_DCN2 = $(addprefix $(AMDDALPATH)/dc/irq/dcn20/,$(IRQ_DCN2))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN2)
###############################################################################
# DCN 21
###############################################################################
IRQ_DCN21 = irq_service_dcn21.o

AMD_DAL_IRQ_DCN21= $(addprefix $(AMDDALPATH)/dc/irq/dcn21/,$(IRQ_DCN21))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN21)

###############################################################################
# DCN 201
###############################################################################
IRQ_DCN201 = irq_service_dcn201.o

AMD_DAL_IRQ_DCN201 = $(addprefix $(AMDDALPATH)/dc/irq/dcn201/,$(IRQ_DCN201))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN201)

###############################################################################
# DCN 30
###############################################################################
IRQ_DCN3 = irq_service_dcn30.o

AMD_DAL_IRQ_DCN3 = $(addprefix $(AMDDALPATH)/dc/irq/dcn30/,$(IRQ_DCN3))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN3)
###############################################################################
# DCN 3_02
###############################################################################
IRQ_DCN3_02 = irq_service_dcn302.o

AMD_DAL_IRQ_DCN3_02 = $(addprefix $(AMDDALPATH)/dc/irq/dcn302/,$(IRQ_DCN3_02))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN3_02)
###############################################################################
# DCN 3_03
###############################################################################
IRQ_DCN3_03 = irq_service_dcn303.o

AMD_DAL_IRQ_DCN3_03 = $(addprefix $(AMDDALPATH)/dc/irq/dcn303/,$(IRQ_DCN3_03))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN3_03)

###############################################################################
# DCN 31
###############################################################################
IRQ_DCN31 = irq_service_dcn31.o

AMD_DAL_IRQ_DCN31= $(addprefix $(AMDDALPATH)/dc/irq/dcn31/,$(IRQ_DCN31))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN31)

###############################################################################
# DCN 314
###############################################################################
IRQ_DCN314 = irq_service_dcn314.o

AMD_DAL_IRQ_DCN314= $(addprefix $(AMDDALPATH)/dc/irq/dcn314/,$(IRQ_DCN314))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN314)

###############################################################################
# DCN 315
###############################################################################
IRQ_DCN315 = irq_service_dcn315.o

AMD_DAL_IRQ_DCN315= $(addprefix $(AMDDALPATH)/dc/irq/dcn315/,$(IRQ_DCN315))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN315)

###############################################################################
# DCN 32
###############################################################################
IRQ_DCN32 = irq_service_dcn32.o

AMD_DAL_IRQ_DCN32= $(addprefix $(AMDDALPATH)/dc/irq/dcn32/,$(IRQ_DCN32))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN32)

###############################################################################
# DCN 35
###############################################################################
IRQ_DCN35 = irq_service_dcn35.o

AMD_DAL_IRQ_DCN35= $(addprefix $(AMDDALPATH)/dc/irq/dcn35/,$(IRQ_DCN35))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN35)

###############################################################################
# DCN 351
###############################################################################
IRQ_DCN351 = irq_service_dcn351.o

AMD_DAL_IRQ_DCN351= $(addprefix $(AMDDALPATH)/dc/irq/dcn351/,$(IRQ_DCN351))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN351)

###############################################################################
# DCN 36
###############################################################################
IRQ_DCN36 = irq_service_dcn36.o

AMD_DAL_IRQ_DCN36= $(addprefix $(AMDDALPATH)/dc/irq/dcn36/,$(IRQ_DCN36))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN36)

###############################################################################
# DCN 401
###############################################################################
IRQ_DCN401 = irq_service_dcn401.o

AMD_DAL_IRQ_DCN401= $(addprefix $(AMDDALPATH)/dc/irq/dcn401/,$(IRQ_DCN401))

AMD_DISPLAY_FILES += $(AMD_DAL_IRQ_DCN401)
