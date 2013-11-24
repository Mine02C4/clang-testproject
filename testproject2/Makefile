# ---[ config ]
PROJNAME=testproject2
SRCS=sub.cc testproject2.cc

BIN=bin
OBJ=obj
BLDDBG=debug
BLDREL=release
ARCH=amd64

CXX=clang++
CXXFLAGS=-Werror -std=c++11 -stdlib=libc++
CXXFLAGSDBG=-O0 -g
CXXFLAGSREL=-O4
LLVMLINK=llvm-link
LLVMLINKFLAGS=
LLC=llc
LLCFLAGS=-march=x86-64 -mcpu=prescott -filetype=obj

CXXEX=cc
BCEX=bc
OBJEX=obj

# ---[ make ]
ifeq ($(DEBUG), 0)
BLD=$(BLDREL)
CXXFLAGS+= $(CXXFLAGSREL)
else
BLD=$(BLDDBG)
CXXFLAGS+= $(CXXFLAGSDBG)
endif

BINDIR=./$(BIN)/$(BLD)/$(ARCH)
OBJDIR=./$(OBJ)/$(BLD)/$(ARCH)
BCS=$(patsubst %.$(CXXEX), $(OBJDIR)/%.$(BCEX), $(SRCS))
MGNAME=_merged
BCFILE=$(OBJDIR)/$(MGNAME).$(SEX)
OBJFILE=$(OBJDIR)/$(MGNAME).$(OBJEX)
BINFILE=$(OBJDIR)/$(MGNAME)
EXEFILE=$(BINDIR)/$(PROJNAME)

.PHONY: bad debug release build check run clean rebuild

bad:	
	@make build DEBUG=$(DEBUG)

all:	
	make build
	make build DEBUG=0

debug:
	@make build DEBUG=1

release:
	@make build DEBUG=0

build:	check $(EXEFILE)

check:
	@mkdir -p $(BINDIR) $(OBJDIR)

run:
	@$(EXEFILE)

clean:
	@rm -rf ./$(OBJ)

rebuild: clean debug

$(BCS):	$(OBJDIR)/%.$(BCEX): %.$(CXXEX)
	@echo "コンパイルしています: $< -> $@"
	@$(CXX) -c -emit-llvm $(CXXFLAGS) $< -o $@

$(BCFILE): $(BCS)
	@echo "リンクしています: $^ -> $@"
	@$(LLVMLINK) $(LLVMLINKFLAGS) $^ -o $@

$(OBJFILE): $(BCFILE)
	@echo "オブジェクトコードに変換しています: $< -> $@"
	@$(LLC) $(LLCFLAGS) $< -o $@

$(BINFILE): $(OBJFILE)
	@echo "リンクしています: $< -> $@"
	@$(CXX) $(CXXFLAGS) $< -o $@

$(EXEFILE): $(BINFILE)
	@echo "コピーしています: $< -> $@"
	@cp $< $@
