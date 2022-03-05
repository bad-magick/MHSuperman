// detail_commctrl_constants.hpp

// Easy GUI Library
//
// Copyright (C) 2008 John Torjo (see http://torjo.com/contact/ for email)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
//
// You can find the latest version of this library at http://www.torjo.com/egui/

#ifndef JOHN_TORJO_WIN32GUI_detail_commctrl_constants
#define JOHN_TORJO_WIN32GUI_detail_commctrl_constants

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif


#ifdef __GNUC__
    #   if __GNUC__ < 3
    #error You need at least gcc 3.2 (recommended 3.3.1+)
    #endif
#endif

/*
    Constants that might not be defined for certain compilers
*/

// ... these might not be defined for GCC
#ifndef TCIF_STATE
#define TCIF_STATE              0x0010
#endif
#ifndef LVIF_INDENT
#define LVIF_INDENT             0x0010
#endif
#ifndef LVIF_NORECOMPUTE
#define LVIF_NORECOMPUTE        0x0800
#endif



#ifndef TBM_SETBUDDY
#define TBM_SETBUDDY            (WM_USER+32) 
#endif
#ifndef TBM_GETBUDDY
#define TBM_GETBUDDY            (WM_USER+33) 
#endif


#ifndef UDM_SETPOS32
#define UDM_SETPOS32            (WM_USER+113)
#endif
#ifndef UDM_GETPOS32
#define UDM_GETPOS32            (WM_USER+114)
#endif

#ifndef HDM_GETIMAGELIST
#define HDM_GETIMAGELIST        (HDM_FIRST + 9)
#endif
#ifndef HDM_SETIMAGELIST
#define HDM_SETIMAGELIST        (HDM_FIRST + 8)
#endif


#ifdef __GNUC__
    typedef struct HDHITTESTINFO
    {
        POINT pt;
        UINT flags;
        int iItem;
    };
#endif


#ifdef __GNUC__
#undef TBIF_BYINDEX // suppress stupid GCC warnings
#define TBIF_BYINDEX            0x80000000
#endif


#ifndef CCM_FIRST
#define CCM_FIRST               0x2000
#endif

#ifndef TBSTATE_ELLIPSES
#define TBSTATE_ELLIPSES        0x40
#endif

#ifndef TBSTATE_MARKED
#define TBSTATE_MARKED          0x80
#endif

#ifndef BTNS_AUTOSIZE
#define BTNS_AUTOSIZE TBSTYLE_AUTOSIZE
#endif
#ifndef BTNS_BUTTON
#define BTNS_BUTTON     TBSTYLE_BUTTON
#endif
#ifndef BTNS_CHECK
#define BTNS_CHECK      TBSTYLE_CHECK       
#endif
#ifndef BTNS_CHECKGROUP
#define BTNS_CHECKGROUP TBSTYLE_CHECKGROUP  
#endif
#ifndef BTNS_DROPDOWN
#define BTNS_DROPDOWN   TBSTYLE_DROPDOWN    
#endif
#ifndef BTNS_NOPREFIX
#define BTNS_NOPREFIX   TBSTYLE_NOPREFIX    
#endif
#ifndef BTNS_SEP
#define BTNS_SEP        TBSTYLE_SEP         
#endif
#ifndef BTNS_WHOLEDROPDOWN
#define BTNS_WHOLEDROPDOWN  0x0080          
#endif
#ifndef SBARS_TOOLTIPS
#define SBARS_TOOLTIPS          0x0800
#endif
#ifndef TVM_GETSCROLLTIME
#define TVM_GETSCROLLTIME              (TV_FIRST + 34)
#endif
#ifndef TVM_SETSCROLLTIME
#define TVM_SETSCROLLTIME              (TV_FIRST + 33)
#endif
#ifndef TVM_GETLINECOLOR
#define TVM_GETLINECOLOR            (TV_FIRST + 41)
#endif
#ifndef TVM_SETLINECOLOR
#define TVM_SETLINECOLOR            (TV_FIRST + 40)
#endif
#ifndef TB_GETIMAGELIST
#define TB_GETIMAGELIST         (WM_USER + 49)
#endif

#ifndef CCM_SETVERSION
#define CCM_SETVERSION          (CCM_FIRST + 0x7)
#endif

#ifndef TB_SETIMAGELIST
#define TB_SETIMAGELIST         (WM_USER + 48)
#endif

#ifndef TB_GETSTYLE
#define TB_GETSTYLE             (WM_USER + 57)
#endif

#ifndef TB_SETSTYLE
#define TB_SETSTYLE             (WM_USER + 56)
#endif

#ifndef TB_GETRECT
#define TB_GETRECT              (WM_USER + 51)
#endif

#ifndef TB_GETTEXTROWS
#define TB_GETTEXTROWS          (WM_USER + 61)
#endif

#ifndef TB_SETBUTTONWIDTH
#define TB_SETBUTTONWIDTH       (WM_USER + 59)
#endif

#ifndef TB_SETINDENT
#define TB_SETINDENT            (WM_USER + 47)
#endif

#ifndef TB_SETMAXTEXTROWS
#define TB_SETMAXTEXTROWS       (WM_USER + 60)
#endif

#ifndef TB_GETHOTITEM
#define TB_GETHOTITEM           (WM_USER + 71)
#endif

#ifndef TB_SETHOTITEM
#define TB_SETHOTITEM           (WM_USER + 72)
#endif

#ifndef TB_SETDRAWTEXTFLAGS
#define TB_SETDRAWTEXTFLAGS     (WM_USER + 70)
#endif

#ifndef TB_SETCOLORSCHEME
#define TB_SETCOLORSCHEME       CCM_SETCOLORSCHEME
#endif

#ifndef TB_GETCOLORSCHEME
#define TB_GETCOLORSCHEME       CCM_GETCOLORSCHEME
#endif

#ifndef TB_GETMAXSIZE
#define TB_GETMAXSIZE           (WM_USER + 83)
#endif

#ifndef TB_GETPADDING
#define TB_GETPADDING           (WM_USER + 86)
#endif

#ifndef TB_SETPADDING
#define TB_SETPADDING           (WM_USER + 87)
#endif

#ifndef TB_HITTEST
#define TB_HITTEST              (WM_USER + 69)
#endif

#ifndef TB_MARKBUTTON
#define TB_MARKBUTTON           (WM_USER + 6)
#endif

#ifndef TB_MOVEBUTTON
#define TB_MOVEBUTTON           (WM_USER + 82)
#endif


#ifndef TB_GETBUTTONINFO
    #ifdef UNICODE
    #define TB_GETBUTTONINFO        (WM_USER + 63)
    #else
    #define TB_GETBUTTONINFO        (WM_USER + 65)
    #endif
#endif

#ifndef TB_SETBUTTONINFO
    #ifdef UNICODE
    #define TB_SETBUTTONINFO        (WM_USER + 64)
    #else
    #define TB_SETBUTTONINFO        (WM_USER + 66)
    #endif
#endif




#ifdef __GNUC__
// note: this is defined in gcc 3.3.1+
#if __GNUC_MINOR__ <= 2
    typedef struct NMTBHOTITEM
    {
        NMHDR   hdr;
        int     idOld;
        int     idNew;
        DWORD   dwFlags;
    } ;
#endif
#endif

#ifndef TBN_HOTITEMCHANGE
#define TBN_HOTITEMCHANGE       (UINT)(TBN_FIRST - 13)
#endif

#ifndef HICF_LEAVING
#define HICF_LEAVING        0x00000020          
#endif


#ifndef ILCF_MOVE
#define ILCF_MOVE   (0x00000000)
#endif

#ifndef ILCF_SWAP
#define ILCF_SWAP   (0x00000001)
#endif


#ifndef TTF_DI_SETITEM
#define TTF_DI_SETITEM          0x8000       
#endif


#ifndef COLOR_HOTLIGHT
#define COLOR_HOTLIGHT          26
#endif


#ifndef MIIM_STRING
#define MIIM_STRING      0x00000040
#endif

#ifndef MIIM_BITMAP
#define MIIM_BITMAP      0x00000080
#endif

#ifndef MIIM_FTYPE
#define MIIM_FTYPE       0x00000100
#endif


#ifndef TTM_SETTITLE
    #ifdef UNICODE
    #define TTM_SETTITLE (WM_USER + 33)
    #else
    #define TTM_SETTITLE (WM_USER + 32)
    #endif
#endif


#ifndef TBSTYLE_EX_MIXEDBUTTONS
#define TBSTYLE_EX_MIXEDBUTTONS             0x00000008
#endif

#ifndef TBSTYLE_EX_HIDECLIPPEDBUTTONS
#define TBSTYLE_EX_HIDECLIPPEDBUTTONS       0x00000010  
#endif


#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED           0x00080000
#endif

#ifndef SS_EDITCONTROL
#define SS_EDITCONTROL      0x00002000L
#endif


#ifndef LBS_COMBOBOX
#define LBS_COMBOBOX          0x8000L
#endif


#ifndef HHT_ONFILTER
#define HHT_ONFILTER            0x0010
#endif

#ifndef HHT_ONFILTERBUTTON
#define HHT_ONFILTERBUTTON      0x0020
#endif

#ifndef LVIS_GLOW
#define LVIS_GLOW               0x0010
#endif

#ifndef LVIS_ACTIVATING
#define LVIS_ACTIVATING         0x0020
#endif

#ifndef RBHT_CHEVRON
#define RBHT_CHEVRON    0x0008
#endif

#ifndef SBT_NOTABPARSING
#define SBT_NOTABPARSING         0x0800
#endif


#ifndef TVIS_EXPANDPARTIAL
#define TVIS_EXPANDPARTIAL      0x0080
#endif



#ifndef CFM_WEIGHT			
#define	CFM_WEIGHT			0x00400000
#endif

#ifndef CFM_BACKCOLOR		
#define CFM_BACKCOLOR		0x04000000
#endif

#ifndef CFM_UNDERLINETYPE	
#define	CFM_UNDERLINETYPE	0x00800000		
#endif

#ifndef CFM_REVAUTHOR
#define CFM_REVAUTHOR		0x00008000
#endif



#ifndef CFM_STYLE			
#define CFM_STYLE			0x00080000		
#endif

#ifndef CFM_LCID			
#define CFM_LCID			0x02000000
#endif

#ifndef CFM_SPACING
#define CFM_SPACING			0x00200000		
#endif

#ifndef CFM_KERNING
#define CFM_KERNING			0x00100000		
#endif

#ifndef CFM_ANIMATION		
#define CFM_ANIMATION		0x00040000		
#endif

#ifndef CFM_EFFECTS 
#define CFM_EFFECTS (CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_COLOR | \
					 CFM_STRIKEOUT | CFE_PROTECTED | CFM_LINK)
#endif


#ifndef CFM_SMALLCAPS		
#define CFM_SMALLCAPS		0x0040	
#endif

#ifndef CFM_ALLCAPS			
#define	CFM_ALLCAPS			0x0080	
#endif

#ifndef CFM_HIDDEN			
#define	CFM_HIDDEN			0x0100	
#endif

#ifndef CFM_OUTLINE			
#define	CFM_OUTLINE			0x0200	
#endif

#ifndef CFM_SHADOW			
#define	CFM_SHADOW			0x0400	
#endif

#ifndef CFM_EMBOSS			
#define	CFM_EMBOSS			0x0800	
#endif

#ifndef CFM_IMPRINT			
#define	CFM_IMPRINT			0x1000	
#endif

#ifndef CFM_DISABLED		
#define CFM_DISABLED		0x2000
#endif

#ifndef CFM_REVISED			
#define	CFM_REVISED			0x4000
#endif



#ifndef CFM_EFFECTS2 
#define	CFM_EFFECTS2 (CFM_EFFECTS | CFM_DISABLED | CFM_SMALLCAPS | CFM_ALLCAPS \
					| CFM_HIDDEN  | CFM_OUTLINE | CFM_SHADOW | CFM_EMBOSS \
					| CFM_IMPRINT | CFM_DISABLED | CFM_REVISED \
					| CFM_SUBSCRIPT | CFM_SUPERSCRIPT | CFM_BACKCOLOR)
#endif



#ifndef CFM_ALL 
#define CFM_ALL (CFM_EFFECTS | CFM_SIZE | CFM_FACE | CFM_OFFSET | CFM_CHARSET)
#endif


#ifndef CFM_ALL2
#define CFM_ALL2	 (CFM_ALL | CFM_EFFECTS2 | CFM_BACKCOLOR | CFM_LCID \
					| CFM_UNDERLINETYPE | CFM_WEIGHT | CFM_REVAUTHOR \
					| CFM_SPACING | CFM_KERNING | CFM_STYLE | CFM_ANIMATION)
#endif


#ifndef SES_EMULATESYSEDIT
#define	SES_EMULATESYSEDIT		1
#endif

#ifndef SES_BEEPONMAXTEXT
#define SES_BEEPONMAXTEXT		2
#endif

#ifndef SES_EXTENDBACKCOLOR
#define	SES_EXTENDBACKCOLOR		4
#endif

#ifndef SES_USEAIMM
#define SES_USEAIMM				64
#endif

#ifndef SES_UPPERCASE
#define SES_UPPERCASE			512
#endif

#ifndef SES_LOWERCASE
#define	SES_LOWERCASE			1024
#endif

#ifndef SES_NOINPUTSEQUENCECHK
#define SES_NOINPUTSEQUENCECHK	2048
#endif

#ifndef SES_XLTCRCRLFTOCR
#define	SES_XLTCRCRLFTOCR		16384
#endif

#ifndef SES_NOIME
#define SES_NOIME				128
#endif

#ifndef SES_BIDI
#define SES_BIDI				4096
#endif

#ifndef SES_SCROLLONKILLFOCUS
#define SES_SCROLLONKILLFOCUS	8192
#endif

#ifndef ENM_PARAGRAPHEXPANDED
#define ENM_PARAGRAPHEXPANDED	0x00000020
#endif

#ifndef ENM_PAGECHANGE			
#define ENM_PAGECHANGE			0x00000040
#endif

#ifndef ENM_LOWFIRTF			
#define ENM_LOWFIRTF			0x08000000
#endif

#ifdef __GNUC__
typedef /* [wire_marshal] */ WORD CLIPFORMAT;
#endif


#ifndef OFN_DONTADDTORECENT          
#define OFN_DONTADDTORECENT          0x02000000
#endif

#ifndef OFN_ENABLEINCLUDENOTIFY      
#define OFN_ENABLEINCLUDENOTIFY      0x00400000     
#endif

#ifndef BIF_NONEWFOLDERBUTTON  
#define BIF_NONEWFOLDERBUTTON  0x0200   
#endif

#ifndef BIF_NOTRANSLATETARGETS 
#define BIF_NOTRANSLATETARGETS 0x0400   
#endif

#ifndef BIF_UAHINT             
#define BIF_UAHINT             0x0100   
#endif

#ifndef OFN_EX_NOPLACESBAR         
#define  OFN_EX_NOPLACESBAR         0x00000001
#endif

#ifndef WM_MENUDRAG 
#define WM_MENUDRAG 0x0123
#endif

#ifndef WM_MENUGETOBJECT                
#define WM_MENUGETOBJECT                0x0124
#endif

#ifndef WM_UNINITMENUPOPUP 
#define WM_UNINITMENUPOPUP 0x0125
#endif

#ifndef WM_MENUCOMMAND                  
#define WM_MENUCOMMAND                  0x0126
#endif

#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 0x020B
#endif

#ifndef WM_XBUTTONUP                    
#define WM_XBUTTONUP                    0x020C
#endif

#ifndef WM_XBUTTONDBLCLK                
#define WM_XBUTTONDBLCLK                0x020D
#endif

#ifndef WM_NCXBUTTONDOWN
#define WM_NCXBUTTONDOWN 0x00AB
#endif

#ifndef WM_NCXBUTTONUP                  
#define WM_NCXBUTTONUP                  0x00AC
#endif

#ifndef WM_NCXBUTTONDBLCLK              
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif

#ifndef WM_NCMOUSEHOVER
#define WM_NCMOUSEHOVER 0x02A0
#endif

#ifndef WM_NCMOUSELEAVE                 
#define WM_NCMOUSELEAVE                 0x02A2
#endif

#ifndef MN_GETHMENU 
#define MN_GETHMENU 0x01E1
#endif

#ifndef WM_CHANGEUISTATE
#define WM_CHANGEUISTATE 0x0127
#endif

#ifndef WM_UPDATEUISTATE                
#define WM_UPDATEUISTATE                0x0128
#endif

#ifndef WM_QUERYUISTATE                 
#define WM_QUERYUISTATE                 0x0129
#endif

#ifndef WM_IME_STARTCOMPOSITION 
#define WM_IME_STARTCOMPOSITION 0x010D
#endif

#ifndef WM_IME_ENDCOMPOSITION           
#define WM_IME_ENDCOMPOSITION           0x010E
#endif

#ifndef WM_IME_COMPOSITION              
#define WM_IME_COMPOSITION              0x010F
#endif

#ifndef WM_IME_SETCONTEXT 
#define WM_IME_SETCONTEXT 0x0281
#endif

#ifndef WM_IME_NOTIFY
#define WM_IME_NOTIFY 0x0282
#endif

#ifndef WM_IME_CONTROL                  
#define WM_IME_CONTROL                  0x0283
#endif

#ifndef WM_IME_COMPOSITIONFULL          
#define WM_IME_COMPOSITIONFULL          0x0284
#endif

#ifndef WM_IME_SELECT                   
#define WM_IME_SELECT                   0x0285
#endif

#ifndef WM_IME_CHAR                     
#define WM_IME_CHAR                     0x0286
#endif

#ifndef WM_IME_REQUEST 
#define WM_IME_REQUEST 0x0288
#endif

#ifndef WM_IME_KEYDOWN                  
#define WM_IME_KEYDOWN                  0x0290
#endif

#ifndef WM_IME_KEYUP                    
#define WM_IME_KEYUP                    0x0291
#endif



#ifndef GRADIENT_FILL_RECT_H 
#define GRADIENT_FILL_RECT_H 0x00000000
#endif


#ifndef GRADIENT_FILL_RECT_V
#define GRADIENT_FILL_RECT_V    0x00000001
#endif

#ifndef GRADIENT_FILL_TRIANGLE  
#define GRADIENT_FILL_TRIANGLE  0x00000002
#endif


#ifndef TCN_FOCUSCHANGE
#define TCN_FOCUSCHANGE         (TCN_FIRST - 4)
#endif


#ifndef TCN_GETOBJECT           
#define TCN_GETOBJECT           (TCN_FIRST - 3)
#endif

#ifndef HDN_FILTERCHANGE
#define HDN_FILTERCHANGE        (HDN_FIRST-12)
#endif

#ifndef HDN_FILTERBTNCLICK      
#define HDN_FILTERBTNCLICK      (HDN_FIRST-13)
#endif

#ifndef LVN_HOTTRACK
#define LVN_HOTTRACK            (LVN_FIRST-21)
#endif

#ifndef RBN_CHEVRONPUSHED
#define RBN_CHEVRONPUSHED   (RBN_FIRST - 10)
#endif

#ifndef RBN_MINMAX
#define RBN_MINMAX          (RBN_FIRST - 21)
#endif

#ifndef TBN_GETOBJECT
#define TBN_GETOBJECT           (TBN_FIRST - 12)
#endif

#ifndef TBN_GETINFOTIP
    #ifdef UNICODE
    #define TBN_GETINFOTIP         (TBN_FIRST - 19)
    #else
    #define TBN_GETINFOTIP         (TBN_FIRST - 18)
    #endif
#endif

#ifndef NM_LDOWN
#define NM_LDOWN                (NM_FIRST-20)
#endif









#ifdef __GNUC__
typedef struct NMTCKEYDOWN
{
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} ;

typedef struct NMLVODSTATECHANGE
{
    NMHDR hdr;
    int iFrom;
    int iTo;
    UINT uNewState;
    UINT uOldState;
} ;

typedef struct NMTVKEYDOWN {
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} ;



#endif



/*
#ifndef 
#define 
#endif

#ifndef 
#define 
#endif

#ifndef 
#define 
#endif

#ifndef 
#define 
#endif



#ifndef 
#define 
#endif


*/



#endif // JOHN_TORJO_WIN32GUI_detail_commctrl_constants
