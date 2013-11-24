# ---i[ config ]
PROJNAME=testproject2
SRCS=sub.cc testproject2.cc

BIN=bin
OBJ=obj
BLDDBG=debug
BLDREL=release
ARCH=any
ARCHI686=i686
ARCHAMD64=amd64

CXX=clang++
CXXFLAGS=-Werror -std=c++11 -stdlib=libc++
CXXFLAGSDBG=-O0 -g
CXXFLAGSREL=-O4
OPT=opt
OPTFLAGS=
OPTFLAGSDBG=-O1
OPTFLAGSREL=-O3
LLVMLINK=llvm-link
LLVMLINKFLAGS=
LLC=llc
LLCFLAGS=-filetype=obj
LLCFLAGSI686=-march=x86 -mcpu=prescott
LLCFLAGSAMD64=-march=x86-64 -mcpu=prescott

CXXEX=cc
BCEX=bc
OBJEX=obj

# ---[ make ]
ifeq ($(DEBUG), 0)
BLD=$(BLDREL)
CXXFLAGS+= $(CXXFLAGSREL)
OPTFLAGS+= $(OPTFLAGSREL)
else
BLD=$(BLDDBG)
CXXFLAGS+= $(CXXFLAGSDBG)
OPTFLAGS+= $(OPTFLAGSDBG)
endif

OBJDIR=./$(OBJ)/$(BLD)/$(ARCH)
BCS=$(patsubst %.$(CXXEX), $(OBJDIR)/%.$(BCEX), $(SRCS))
BCOPTS=$(patsubst %.$(CXXEX), $(OBJDIR)/%_opt.$(BCEX), $(SRCS))
MGNAME=_merged
BCFILE=$(OBJDIR)/$(MGNAME).$(BCEX)
BCOPTFILE=$(OBJDIR)/$(MGNAME)_opt.$(BCEX)

ifeq ($(arch), x86-64)
LCCFLAGS+= $(LCCFLAGSAMD64)
OBJDIRARCH=./$(OBJ)/$(BLD)/$(ARCHAMD64)
BINDIRARCH=./$(BIN)/$(BLD)/$(ARCHAMD64)
else
LCCFLAGS+= $(LCCFLAGSI686)
OBJDIRARCH=./$(OBJ)/$(BLD)/$(ARCHI686)
BINDIRARCH=./$(BIN)/$(BLD)/$(ARCHI686)
endif

OBJFILE=$(OBJDIRARCH)/$(MGNAME).$(OBJEX)
BINFILE=$(OBJDIRARCH)/$(MGNAME)
EXEFILE=$(BINDIRARCH)/$(PROJNAME)

.PHONY: bad debug release build check run clean rebuild

bad:	
	@make build DEBUG=$(DEBUG)

all:	
	make build arch=x86
	make build arch=x86 DEBUG=0
	make build arch=x86-64
	make build arch=x86-64 DEBUG=0

debug:
	@make build DEBUG=1

release:
	@make build DEBUG=0

build:	check $(EXEFILE)

check:
	@mkdir -p $(OBJDIR) $(OBJDIRARCH) $(BINDIRARCH)

run:
	@$(EXEFILE)

clean:
	@rm -rf ./$(OBJ)

rebuild: clean debug

$(BCS):	$(OBJDIR)/%.$(BCEX): %.$(CXXEX)
	@echo "コンパイルしています: $< -> $@"
	@$(CXX) -c -emit-llvm $(CXXFLAGS) $< -o $@

$(BCOPTS): %_opt.$(BCEX): %.$(BCEX)
	@echo "最適化しています: $< -> $@"
	@$(OPT) $(OPTFLAGS) $^ -o $@

$(BCFILE): $(BCOPTS)
	@echo "リンクしています: $^ -> $@"
	@$(LLVMLINK) $(LLVMLINKFLAGS) $^ -o $@

$(BCOPTFILE): $(BCFILE)
	@echo "最適化しています: $^ -> $@"
	@$(OPT) $(OPTFLAGS) $^ -o $@

$(OBJFILE): $(BCOPTFILE)
	@echo "オブジェクトコードに変換しています: $< -> $@"
	@$(LLC) $(LLCFLAGS) $< -o $@

$(BINFILE): $(OBJFILE)
	@echo "リンクしています: $< -> $@"
	@$(CXX) $(CXXFLAGS) $< -o $@

$(EXEFILE): $(BINFILE)
	@echo "コピーしています: $< -> $@"
	@cp $< $@
