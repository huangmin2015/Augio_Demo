
XOPTS = -I"C:/ti/xdctools_3_32_01_22_core/packages/" -Dxdc_target_types__=C:/ti/bios_6_46_05_55/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

vpath % C:/ti/bios_6_46_05_55/packages/ti/sysbios/
vpath %.c C:/ti/xdctools_3_32_01_22_core/packages/

CCOPTS    = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -o3 -g --optimize_with_debug  -Dti_sysbios_family_c64p_Exception_enableExternalMPC__D=FALSE -Dti_sysbios_family_c64p_Exception_enablePrint__D=TRUE -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE

XDC_ROOT  = C:/ti/xdctools_3_32_01_22_core/packages/

BIOS_ROOT = C:/ti/bios_6_46_05_55/packages/ti/sysbios/

BIOS_DEFS =  -Dti_sysbios_BIOS_swiEnabled__D=TRUE -Dti_sysbios_BIOS_taskEnabled__D=TRUE -Dti_sysbios_BIOS_clockEnabled__D=TRUE -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=TRUE -Dti_sysbios_knl_Task_moduleStateCheckFlag__D=FALSE -Dti_sysbios_knl_Task_objectCheckFlag__D=FALSE -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Swi_DISABLE_ALL_HOOKS -Dti_sysbios_BIOS_smpEnabled__D=FALSE -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_knl_Swi_numPriorities__D=16 -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=FALSE -Dti_sysbios_knl_Task_numPriorities__D=16 -Dti_sysbios_knl_Task_checkStackFlag__D=TRUE -Dti_sysbios_knl_Task_initStackFlag__D=TRUE -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_TIMER -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC -Dti_sysbios_hal_Core_delegate_getId=ti_sysbios_hal_CoreNull_getId__E -Dti_sysbios_hal_Core_delegate_interruptCore=ti_sysbios_hal_CoreNull_interruptCore__E -Dti_sysbios_hal_Core_delegate_lock=ti_sysbios_hal_CoreNull_lock__E -Dti_sysbios_hal_Core_delegate_unlock=ti_sysbios_hal_CoreNull_unlock__E -Dti_sysbios_hal_Core_numCores__D=1 -Dti_sysbios_hal_CoreNull_numCores__D=1 -Dti_sysbios_utils_Load_taskEnabled__D=TRUE -Dti_sysbios_utils_Load_swiEnabled__D=FALSE -Dti_sysbios_utils_Load_hwiEnabled__D=FALSE -Dti_sysbios_family_c64p_Hwi_dispatcherSwiSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherTaskSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherAutoNestingSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherIrpTrackingSupport__D=TRUE -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE -Dti_sysbios_knl_Semaphore_supportsPriority__D=TRUE 

BIOS_INC  = -I"C:/ti/bios_6_46_05_55/packages/"

INCS =  $(BIOS_INC) -I"C:/ti/bios_6_46_05_55/packages/" -I"C:/ti/pdk_am57xx_1_0_7/packages/" -I"C:/ti/edma3_lld_2_12_04_28/packages/" -I"C:/ti/ipc_3_46_00_02/packages/" -I"C:/ti/ndk_2_25_01_11/packages/" -I"C:/ti/uia_2_00_06_52/packages/" -I"C:/ti/ccsv7/ccs_base/" -I"C:/ti/xdctools_3_32_01_22_core/packages/" -I"../" -I"/packages//" 

CC = C:/ti/ti-cgt-c6000_8.1.3/bin/cl6x -c $(CCOPTS) -I C:/ti/ti-cgt-c6000_8.1.3/include
ASM = C:/ti/ti-cgt-c6000_8.1.3/bin/cl6x -c $(CCOPTS) -I C:/ti/ti-cgt-c6000_8.1.3/include
AR = C:/ti/ti-cgt-c6000_8.1.3/bin/ar6x rq

DEL = C:/ti/xdctools_3_32_01_22_core/packages/../bin/rm -f
CP = C:/ti/xdctools_3_32_01_22_core/packages/../bin/cp -f

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BIOS_DEFS) $(XOPTS) $(INCS) $<
endef

all: sysbios.ae66

c64p_Exception_asm.obj: family/c64p/Exception_asm.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Exception_asm.obj

c64p_Hwi_asm.obj: family/c64p/Hwi_asm.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_asm.obj

c64p_Hwi_asm_switch.obj: family/c64p/Hwi_asm_switch.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_asm_switch.obj

c64p_Hwi_disp_always.obj: family/c64p/Hwi_disp_always.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_disp_always.obj

ti_tls_get_tp.obj: rts/ti/tls_get_tp.asm makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=ti_tls_get_tp.obj

c62_TaskSupport_asm.obj: family/c62/TaskSupport_asm.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c62_TaskSupport_asm.obj

dmtimer_Timer_asm.obj: timers/dmtimer/Timer_asm.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=dmtimer_Timer_asm.obj


BIOS.obj: BIOS.c family/c64p/EventCombiner.c family/c64p/Exception.c family/c64p/Hwi.c family/c64p/Hwi_startup.c family/c64p/TimestampProvider.c knl/Clock.c knl/Idle.c knl/Intrinsics.c knl/Queue.c knl/Semaphore.c knl/Swi.c knl/Swi_andn.c knl/Task.c io/DEV.c io/GIO.c io/IOM_stub.c hal/Cache.c hal/Hwi.c hal/Hwi_stack.c hal/Hwi_startup.c family/shared/vayu/IntXbar.c family/shared/vayu/TimerSupport.c heaps/HeapMem.c utils/Load.c utils/Load_CPU.c rts/ti/ThreadLocalStorage.c family/c66/Cache.c family/c62/TaskSupport.c family/c62/IntrinsicsSupport.c gates/GateHwi.c gates/GateMutex.c xdcruntime/SemThreadSupport.c timers/dmtimer/Timer.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BIOS_DEFS) $(XOPTS) $(INCS) \
	$(BIOS_ROOT)BIOS.c \
	$(BIOS_ROOT)family/c64p/EventCombiner.c \
	$(BIOS_ROOT)family/c64p/Exception.c \
	$(BIOS_ROOT)family/c64p/Hwi.c \
	$(BIOS_ROOT)family/c64p/Hwi_startup.c \
	$(BIOS_ROOT)family/c64p/TimestampProvider.c \
	$(BIOS_ROOT)knl/Clock.c \
	$(BIOS_ROOT)knl/Idle.c \
	$(BIOS_ROOT)knl/Intrinsics.c \
	$(BIOS_ROOT)knl/Queue.c \
	$(BIOS_ROOT)knl/Semaphore.c \
	$(BIOS_ROOT)knl/Swi.c \
	$(BIOS_ROOT)knl/Swi_andn.c \
	$(BIOS_ROOT)knl/Task.c \
	$(BIOS_ROOT)io/DEV.c \
	$(BIOS_ROOT)io/GIO.c \
	$(BIOS_ROOT)io/IOM_stub.c \
	$(BIOS_ROOT)hal/Cache.c \
	$(BIOS_ROOT)hal/Hwi.c \
	$(BIOS_ROOT)hal/Hwi_stack.c \
	$(BIOS_ROOT)hal/Hwi_startup.c \
	$(BIOS_ROOT)family/shared/vayu/IntXbar.c \
	$(BIOS_ROOT)family/shared/vayu/TimerSupport.c \
	$(BIOS_ROOT)heaps/HeapMem.c \
	$(BIOS_ROOT)utils/Load.c \
	$(BIOS_ROOT)utils/Load_CPU.c \
	$(BIOS_ROOT)rts/ti/ThreadLocalStorage.c \
	$(BIOS_ROOT)family/c66/Cache.c \
	$(BIOS_ROOT)family/c62/TaskSupport.c \
	$(BIOS_ROOT)family/c62/IntrinsicsSupport.c \
	$(BIOS_ROOT)gates/GateHwi.c \
	$(BIOS_ROOT)gates/GateMutex.c \
	$(BIOS_ROOT)xdcruntime/SemThreadSupport.c \
	$(BIOS_ROOT)timers/dmtimer/Timer.c \

sysbios.ae66: BIOS.obj c64p_Exception_asm.obj c64p_Hwi_asm.obj c64p_Hwi_asm_switch.obj c64p_Hwi_disp_always.obj ti_tls_get_tp.obj c62_TaskSupport_asm.obj dmtimer_Timer_asm.obj
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@$(DEL) ..\makefile.libs
	@-$(call RM, *)
