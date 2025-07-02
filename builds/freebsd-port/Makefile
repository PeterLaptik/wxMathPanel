PORTNAME=		wxmathpanel
DISTVERSION=	VERSION_NUM
PORTREVISION=	1
CATEGORIES=	x11-toolkits
MASTER_SITES=	https://github.com/PeterLaptik/wxMathPanel/releases/download/${DISTVERSION}/
DISTNAME=	wxmathpanel-src-${DISTVERSION}

MAINTAINER=	Peter Laptik
COMMENT=	Math plot widget for wxWidgets library
WWW=		https://github.com/PeterLaptik/wxMathPanel

LICENSE=	BSD2CLAUSE

GNU_CONFIGURE=yes

USE_WX=		3.0+

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/include/wxmathpanel
	${CP} ${WRKSRC}/Build/include/wxmathpanel/*  ${STAGEDIR}${PREFIX}/include/wxmathpanel/
	${CP} ${WRKSRC}/Build/lib/*  ${STAGEDIR}${PREFIX}/lib/

.include <bsd.port.mk>
