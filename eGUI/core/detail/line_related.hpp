// line_related.hpp

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

#ifndef JOHN_TORJO_line_related
#define JOHN_TORJO_line_related

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif




namespace egui { namespace types {
/*
    Wrappers over some Win32 raw structures
*/

struct rectangle ;
typedef int line_int_type;


/** for inflating rectangles */
enum {
    inflate_to_right = 1, inflate_to_left = 2,
    inflate_to_top = 4, inflate_to_bottom = 8
};


/**
    @brief contains a size (width and height)
*/
struct size {
    line_int_type width, height;

    size(line_int_type width = 0, line_int_type height = 0) : width(width), height(height) {
    }
};


/**
    @brief point
*/
struct point {
    line_int_type x, y;
    point(line_int_type x = 0, line_int_type y = 0) : x(x), y(y) {
    }

    point convert(const wnd<> & from, const wnd<> & to) const;
    bool is_in_rect(const rectangle & r) const;
};



/** 
    @brief Contains a rectangle
*/
struct rectangle {
    point start;
    typedef size size_type;
    size_type size;

    rectangle(point start = point(), size_type sz = size_type() ) : start(start), size(sz) {}
    rectangle(line_int_type x, line_int_type y, line_int_type width, line_int_type height) : start(x,y), size(width,height) {}


    line_int_type height() const { return size.height; }
    line_int_type width() const { return size.width; }

    point top_left() const { return start; }
    point bottom_right() const { return point(start.x + size.width, start.y + size.height); }

    /** 
        Returns a new rectangle, of the same size, but whose' top-left point
        is the given point.
    */
    rectangle to_point(const point& p) const { 
        return rectangle(p.x, p.y, p.x - start.x , p.y - start.y); 
    }

    rectangle convert(const wnd<> & from, const wnd<> & to) const;
    bool contains_point(const point & p) const; 

    rectangle intersect(const rectangle& other) const; 
    rectangle merge(const rectangle& other) const;
    rectangle inflate(const size_type&, int direction = inflate_to_right | inflate_to_bottom) const;

	// steven: added
	void offset(int x, int y);
    void offset(const size_type & sz) { offset(sz.width, sz.height); }
	
	/** deflates this rectangle by size */
	void deflate(const size_type& size)	{ inflate(size, inflate_to_left | inflate_to_top); }	
};

/**
The invalid rectangle.

Returned in case there's no valid return (for instance, there's no intersection between two rects.)
*/
const rectangle invalid_rect = rectangle(0,0,-1,-1); 




/**
    @brief Represents an RGB color

    Setters can be chained, like this:
    <tt>color().red(14).blue(100); </tt>
*/
struct color {
    color(int r = 0, int g = 0, int b = 0);

    const int red() const       ;
    const int green() const     ;
    const int blue() const      ;

    color & red(int val) ;
    color & green(int val);
    color & blue(int val) ;

    static color invalid_ ;
    bool equal(const color & other) const { return m_rgb == other.m_rgb; }
private:
    static color invalid_color() ;

private:
    unsigned long m_rgb;
};

inline bool operator==(const color & a, const color & b) {
    return a.equal(b);
}
inline bool operator!=(const color & a, const color & b) {
    return !( a == b);
}



inline bool operator==(const point & a, const point & b) {
    return a.x == b.x && a.y == b.y;
}
inline bool operator!=(const point & a, const point & b) {
    return !( a == b);
}


inline bool operator==(const size & a, const size & b) {
    return a.width == b.width && a.height == b.height;
}
inline bool operator!=(const size & a, const size & b) {
    return !( a == b);
}

inline size &operator+=(size & dest, const size & sz) {
    dest.width += sz.width;
    dest.height += sz.height;
    return dest;
}



inline point &operator+=(point & p, const size & sz) {
    p.x += sz.width;
    p.y += sz.height;
    return p;
}
inline point &operator-=(point & p, const size & sz) {
    p.x -= sz.width;
    p.y -= sz.height;
    return p;
}

inline point operator+(const point & p, const size & sz) {
    point result = p;
    result += sz;
    return result;
}
inline point operator-(const point & p, const size & sz) {
    point result = p;
    result -= sz;
    return result;
}


inline rectangle &operator+=(rectangle & r, const size & sz) {
    r.size += sz;
    return r;
}
inline rectangle &operator-=(rectangle & r, const size & sz) {
    return r += size(-sz.width, -sz.height);
}

inline rectangle operator+(const rectangle & r, const size & sz) {
    rectangle result = r;
    result += sz;
    return result;
}
inline rectangle operator-(const rectangle & r, const size & sz) {
    rectangle result = r;
    result -= sz;
    return result;
}

inline bool operator==(const rectangle & a, const rectangle & b) {
    return a.start == b.start && a.size == b.size;
}
inline bool operator!=(const rectangle & a, const rectangle & b) {
    return !( a == b);
}






}}


#endif 
