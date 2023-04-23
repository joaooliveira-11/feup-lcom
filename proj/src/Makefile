# Nome do binário. Tem de ser "proj".
PROG=proj

# Indicar as pastas de todos os ficheiros a compilar.
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/graphics
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/view/
.PATH: ${.CURDIR}/controller/util


# Ficheiros ".c" a compilar. Têm de estar contidos nas pastas indicadas no passo anterior.
SRCS = 	proj.c timer.c utils.c graphics.c keyboard.c mouse.c sprite.c model.c view.c KBC.c

# Flags de compilação
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# Dependências
DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>