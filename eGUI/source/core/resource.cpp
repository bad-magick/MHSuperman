// template.cpp

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

#include "stdafx_core.h"
#include "egui/core/wnd.hpp"
#include "egui/core/detail/window_manager.hpp"
#include "egui/core/win32/raw.hpp"
#include "egui/core/detail/building_egui.hpp"

namespace egui { namespace types {

namespace {
    // throws if the resource is NULL (it was not loaded)
    template<class res_type> res_type throw_if_cannot_load_res(res_type val) {
        if ( val) return val;
        throw exception( GUI_STR("could not load resource"));
    }

    void throw_if_null(const resource_top & r) {
        if ( !r)
            throw exception( GUI_STR("un-initialized resource"));
    }
	/* retrieves the logical object describing the properties of this gdi object (for example a LOGPEN for a pen) */
	template<class log_type> log_type get_log_object(resource_top::id_type h) {
		log_type obj = { 0 };		
		::GetObject( (HGDIOBJ)h, sizeof(obj), &obj);
		return obj;
	}


    resource_top::id_type clone_icon(resource_top::id_type h) {
        void* r = throw_if_cannot_load_res( CopyImage(h, IMAGE_ICON, 0, 0, 0) );
        return r;
    }

    resource_top::id_type clone_bitmap(resource_top::id_type h) {
        void* r = throw_if_cannot_load_res( CopyImage(h, IMAGE_BITMAP, 0, 0, 0) );
        return r;
    }
    resource_top::id_type clone_image_list(resource_top::id_type h) {
        void* r = throw_if_cannot_load_res( ImageList_Duplicate( (HIMAGELIST)h) );
        return r;
    }
    resource_top::id_type clone_pen(resource_top::id_type h) {
        LOGPEN log = get_log_object<LOGPEN>(h);
        void* r = throw_if_cannot_load_res( ::CreatePenIndirect(&log) );
        return r;
    }
    resource_top::id_type clone_font(resource_top::id_type h) {
        LOGFONT log = get_log_object<LOGFONT>(h);
        void* r = throw_if_cannot_load_res( ::CreateFontIndirect(&log) );
        return r;
    }
    resource_top::id_type clone_brush(resource_top::id_type h) {
        LOGBRUSH log = get_log_object<LOGBRUSH>(h);
        void* r = throw_if_cannot_load_res( ::CreateBrushIndirect(&log) );
        return r;
    }


    void destroy_resource(resource_top::id_holder * h) {
        if ( !h) 
            return;
        if ( h->owns)
            ::DeleteObject(h->id );
        delete h;
    }

    void destroy_image_list(resource_top::id_holder * h) {
        if ( !h) 
            return;
        if ( h->owns)
            ::ImageList_Destroy( (HIMAGELIST)h->id);
        delete h;
    }

}

resource_top::resource_top(destroy_func destroyer, clone_func cloner, id_type id ) 
        : destroy_id(destroyer), clone_id(cloner) {
    set_id(id);
}
resource_top::resource_top(destroy_func destroyer, clone_func cloner, id_type_ptr id ) 
        : destroy_id(destroyer), clone_id(cloner) {
    set_cloned_id(id);
}

resource_top::resource_top(const resource_top & other, const do_clone&) : destroy_id(other.destroy_id), clone_id(other.clone_id) {
    set_cloned_id( other.clone() );
}
resource_top::~resource_top() {}



void resource_top::set_cloned_id(id_type_ptr id) {
    m_id = id;
}

void resource_top::set_id(id_type id) {
    using namespace boost;
    m_id = id_type_ptr( new id_holder(id) , destroy_id);
}

resource_top::id_type_ptr resource_top::clone() const {
    id_type id = clone_id( m_id.get()->id);
    return id_type_ptr( new id_holder(id), destroy_id);
}

void resource_top::set_owns(bool b) {
    m_id->owns = b;
}


////////////////////////////////////////////////////////////
// constructors

bitmap_base::bitmap_base(id_type_ptr p) : resource_top(destroy_resource, clone_bitmap, p) {}
bitmap_base::bitmap_base(id_type id ) : resource_top(destroy_resource, clone_bitmap, id) {}

brush_base::brush_base(id_type_ptr p) : resource_top(destroy_resource, clone_brush, p) {}
brush_base::brush_base(id_type id ) : resource_top(destroy_resource, clone_brush, id) {}

font_base::font_base(id_type_ptr p) : resource_top(destroy_resource, clone_font, p) {}
font_base::font_base(id_type id ) : resource_top(destroy_resource, clone_font, id) {}

icon_base::icon_base(id_type_ptr p) : resource_top(destroy_resource, clone_icon, p) {}
icon_base::icon_base(id_type id ) : resource_top(destroy_resource, clone_icon, id) {}

image_list_base::image_list_base(id_type_ptr p) : resource_top(destroy_image_list, clone_image_list, p) {}
image_list_base::image_list_base(id_type id ) : resource_top(destroy_image_list, clone_image_list, id) {}

pen_base::pen_base(id_type_ptr p) : resource_top(destroy_resource, clone_pen, p) {}
pen_base::pen_base(id_type id ) : resource_top(destroy_resource, clone_pen, id) {}



temporary_bitmap::temporary_bitmap(id_type id) : base_type(id) {
    set_owns(false);    
}
temporary_bitmap::temporary_bitmap(const bitmap& src) : base_type(src) {
    set_owns(false);
}
bitmap::bitmap(const temporary_bitmap & src) : base_type(src) {
}

temporary_brush::temporary_brush(id_type id) : base_type(id) {
    set_owns(false);    
}
temporary_brush::temporary_brush(const brush& src) : base_type(src) {
    set_owns(false);
}
brush::brush(const temporary_brush & src) : base_type(src) {
}

temporary_font::temporary_font(id_type id) : base_type(id) {
    set_owns(false);    
}
temporary_font::temporary_font(const font& src) : base_type(src) {
    set_owns(false);
}
font::font(const temporary_font & src) : base_type(src) {
}

temporary_icon::temporary_icon(const icon& src) : base_type(src) {
    set_owns(false);
}
temporary_icon::temporary_icon(id_type id) : base_type(id) {
    set_owns(false);    
}
icon::icon(const temporary_icon & src) : base_type(src) {
}

temporary_image_list::temporary_image_list(id_type id) : base_type(id) {
    set_owns(false);    
}
temporary_image_list::temporary_image_list(const image_list& src) : base_type(src) {
    set_owns(false);
}
image_list::image_list(const temporary_image_list & src) : base_type(src) {
}

temporary_pen::temporary_pen(id_type id) : base_type(id) {
    set_owns(false);
}
temporary_pen::temporary_pen(const pen& src) : base_type(src) {
    set_owns(false);
}
pen::pen(const temporary_pen & src) : base_type(src) {
}

////////////////////////////////////////////////////////////
// Bitmap

bitmap::bitmap(int id) {
    HINSTANCE inst = detail::window_manager::inst().find_instance_having_resource(id, RT_BITMAP);
    set_id( ::LoadImage(inst, MAKEINTRESOURCE(id), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR ));
    throw_if_null( *this);
}
bitmap::bitmap(int width, int height, int planes , int bits_per_pixel , const void* bits ) {
    set_id( ::CreateBitmap(width, height, planes, bits_per_pixel, bits) );
    throw_if_null( *this);
}


////////////////////////////////////////////////////////////
// icon

icon::icon(int id) {
    HINSTANCE inst = detail::window_manager::inst().find_instance_having_resource(id, RT_ICON);
    set_id( ::LoadImage(inst, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR ));
    throw_if_null( *this);
}
icon::icon(int id, size desired_size) {
    HINSTANCE inst = detail::window_manager::inst().find_instance_having_resource(id, RT_ICON);
    set_id( ::LoadImage(inst, MAKEINTRESOURCE(id), IMAGE_ICON, desired_size.width, desired_size.height, LR_DEFAULTCOLOR ));
    throw_if_null( *this);
}

////////////////////////////////////////////////////////////
// image list

image_list::image_list(int cx, int cy, int initial_count , int grow_by ) {
    set_id( ImageList_Create(cx,cy,ILC_COLOR8,initial_count,grow_by));
    throw_if_null( *this);
}
image_list::image_list(int id, int cx, int grow , color c ) {
    HINSTANCE inst = detail::window_manager::inst().find_instance_having_resource(id, RT_BITMAP);
    set_id( ImageList_LoadImage( inst, MAKEINTRESOURCE(id), cx, grow, win32::to(c), IMAGE_BITMAP, LR_DEFAULTCOLOR) );
    throw_if_null( *this);
}
image_list::image_list(const string & file_name, int cx, int grow , color c ) {
    set_id( ImageList_LoadImage( 0, file_name.c_str(), cx, grow, win32::to(c), IMAGE_BITMAP, LR_LOADFROMFILE | LR_DEFAULTCOLOR));
    throw_if_null( *this);
}


void image_list_base::add_image(const temporary_bitmap & bmp) { 
    ImageList_Add( (HIMAGELIST)id(), win32::to(bmp), 0);
}
void image_list_base::add_image(const temporary_bitmap & bmp, const temporary_bitmap & mask) { 
    ImageList_Add( (HIMAGELIST)id(), win32::to(bmp), win32::to(mask));
}
void image_list_base::add_image(const temporary_bitmap & bmp, color mask) { 
    ImageList_AddMasked( (HIMAGELIST)id(), win32::to(bmp), win32::to(mask));
}

void image_list_base::copy(int from_idx, int to_idx) {
    // FIXME look at newer versions of gcc - has this improved?
    // note: gcc 3.3.1 has a very old libcomctl32.a
#if !defined(__GNUC__)
        ImageList_Copy( (HIMAGELIST)id(), to_idx, (HIMAGELIST)id(), from_idx, ILCF_MOVE);
#endif
}
void image_list_base::swap(int src_idx, int dest_idx) { 
    // FIXME look at newer versions of gcc - has this improved?
    // note: gcc 3.3.1 has a very old libcomctl32.a
#if !defined(__GNUC__)
        ImageList_Copy( (HIMAGELIST)id(), dest_idx, (HIMAGELIST)id(), src_idx, ILCF_SWAP);
#endif
}


////////////////////////////////////////////////////////////
//

/** returns the brush's color */
color brush_base::color() const {
    return get_log_object<LOGBRUSH>( id() ).lbColor;
}
/** sets the brush's color */
void brush_base::color(types::color cr) {
    LOGBRUSH log = get_log_object<LOGBRUSH>( id() );
    if (log.lbColor != win32::to(cr) ) {
        log.lbColor = win32::to(cr);
        bool owns_ = owns();
        set_id( ::CreateBrushIndirect(&log) );
        set_owns(owns_);
	}		
}

/** returns the brush's style */
brush_style::type brush_base::style() const {
    return (brush_style::type) get_log_object<LOGBRUSH>( id() ).lbStyle;
}
/** sets the brush's style */
void brush_base::style(brush_style::type s) {
    LOGBRUSH log = get_log_object<LOGBRUSH>( id() );
    if (log.lbStyle != s ) {
        log.lbStyle = s;
        bool owns_ = owns();
        set_id( ::CreateBrushIndirect(&log) );
        set_owns(owns_);
	}		
}
/** returns the system color brush at color index idx */
temporary_brush brush_base::sys_color_brush(sys_color::type idx) {
	return ::GetSysColorBrush(idx);
}

temporary_brush brush::solid_brush(types::color c) {
    return ::CreateSolidBrush( win32::to(c) );
}




////////////////////////////////////////////////////////////
// font

namespace {
    void to_win32(const font::info_type & egui, LOGFONT & lf) {
        EGUI_TO_WIN32(egui, lf, height, lfHeight);
        EGUI_TO_WIN32(egui, lf, weight, lfWeight);
        EGUI_TO_WIN32(egui, lf, italic, lfItalic);
        EGUI_TO_WIN32(egui, lf, underline, lfUnderline);
        EGUI_TO_WIN32(egui, lf, strike_out, lfStrikeOut);
        EGUI_TO_WIN32(egui, lf, width, lfWidth);
        EGUI_TO_WIN32(egui, lf, quality, lfQuality);
        EGUI_TO_WIN32(egui, lf, output_precision, lfOutPrecision);
        EGUI_TO_WIN32(egui, lf, clip_precision, lfClipPrecision);
        EGUI_TO_WIN32(egui, lf, escapement, lfEscapement);
        EGUI_TO_WIN32(egui, lf, orientation, lfOrientation);
        EGUI_TO_WIN32(egui, lf, charset, lfCharSet);
        EGUI_TO_WIN32(egui, lf, pitch_and_family, lfPitchAndFamily);
        string name = egui.name;
        if ( name.size() > LF_FACESIZE)
            name.reserve(LF_FACESIZE);
        std::copy( name.begin(), name.end(), lf.lfFaceName);
    }
    void from_win32(font::info_type & egui, const LOGFONT & lf) {
        EGUI_FROM_WIN32(egui, lf, height, lfHeight);
        EGUI_FROM_WIN32(egui, (font_weight::type)lf, weight, lfWeight);
        EGUI_FROM_WIN32(egui, lf, italic, lfItalic != 0);
        EGUI_FROM_WIN32(egui, lf, underline, lfUnderline != 0);
        EGUI_FROM_WIN32(egui, lf, strike_out, lfStrikeOut != 0);
        EGUI_FROM_WIN32(egui, lf, width, lfWidth);
        EGUI_FROM_WIN32(egui, lf, quality, lfQuality);
        EGUI_FROM_WIN32(egui, lf, output_precision, lfOutPrecision);
        EGUI_FROM_WIN32(egui, lf, clip_precision, lfClipPrecision);
        EGUI_FROM_WIN32(egui, lf, escapement, lfEscapement);
        EGUI_FROM_WIN32(egui, lf, orientation, lfOrientation);
        EGUI_FROM_WIN32(egui, lf, charset, lfCharSet);
        EGUI_FROM_WIN32(egui, lf, pitch_and_family, lfPitchAndFamily);
        egui.name.resize(LF_FACESIZE);
        std::copy(lf.lfFaceName, lf.lfFaceName + LF_FACESIZE, egui.name.begin());
        string::size_type nul_char = egui.name.find( (char_)0);
        if ( nul_char != string::npos)
            egui.name = egui.name.substr(0, nul_char);
    }
}

font::info_type::info_type(const string & name , int height )
    : name(name)
    , height(height)
    , weight(font_weight::dont_care)
    , italic(false)
    , underline(false)
    , strike_out(false)
    , width(0)
    , quality(DEFAULT_QUALITY)
    , output_precision(OUT_DEFAULT_PRECIS)
    , clip_precision(CLIP_DEFAULT_PRECIS)
    , escapement(0)
    , orientation(0)
    , charset(DEFAULT_CHARSET)
    , pitch_and_family (DEFAULT_PITCH) {
}

void font::info_type::height_in_points(int point_height) {
    HDC hDC = ::GetDC( ::GetActiveWindow() );
    if ( !hDC) 
        hDC = ::GetDC( ::GetForegroundWindow() );
    assert(hDC);
    height = -MulDiv(point_height, GetDeviceCaps(hDC, LOGPIXELSY), 72);
}

bool font::info_type::bold() const {
    return weight >= font_weight::bold;
}
void font::info_type::bold(bool b) {
    if ( b)
        weight = font_weight::bold;
    else
        weight = font_weight::normal;
}



void font_base::create(const info_type& font_info) {
    if ( *this) {
        // we already have a font - we recreate it
        LOGFONT lf = get_log_object<LOGFONT>( id() );
        to_win32(font_info, lf);
        recreate(&lf);
    }
    else {
        // we don't have a font yet - create it now
        LOGFONT lf = { 0 };
        to_win32(font_info, lf);
        recreate(&lf);
    }
}


void font_base::recreate(void * logfont) {
    LOGFONT * lf = (LOGFONT*)logfont;
    bool owns_ = owns();
    set_id( ::CreateFontIndirect(lf) );
    set_owns(owns_);
}

font::info_type font_base::info() const {
    LOGFONT lf = get_log_object<LOGFONT>( id() );
    info_type i;
    from_win32(i, lf);
    return i;
}

void font_base::info(const info_type & inf) {
    create(inf);
}

font::font( font_base::info_type fnt_info) {
    if ( fnt_info.name.empty())
        fnt_info.name = GUI_STR("Tahoma");
    info(fnt_info);
    throw_if_null( *this);
}


////////////////////////////////////////////////////////////
// pen

pen::pen(color c, int width , pen_style::type style) {
    set_id( ::CreatePen(style, width, win32::to(c)) );
    throw_if_null( *this);
}


////////////////////////////////////////////////////////////
//

}}

// End of file
