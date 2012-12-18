#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/Data/_DEVTO~1/CODECO~1/grace_1_10_04_36/packages;C:/Data/_DEVTO~1/CODECO~1/ccsv5/ccs_base;C:/Data/workdir/msp430/final/.config
override XDCROOT = C:/Data/_DEVTO~1/CODECO~1/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/Data/_DEVTO~1/CODECO~1/grace_1_10_04_36/packages;C:/Data/_DEVTO~1/CODECO~1/ccsv5/ccs_base;C:/Data/workdir/msp430/final/.config;C:/Data/_DEVTO~1/CODECO~1/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
