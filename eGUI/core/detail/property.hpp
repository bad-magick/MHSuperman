// property.hpp

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


#ifndef JT07022008_property_HPP_DEFINED
#define JT07022008_property_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include "egui/core/detail/fwd.hpp"

namespace egui {

struct os {
  typedef enum type {
    win_2k          = 0,
    win_2k_sp4      = 1000,
    win_xp          = 2000,
    win_xp_sp2      = 3000,
    win_vista       = 4000
  };
};

#ifndef EGUI_OS
// os::win_xp_sp2
#define EGUI_OS 3000
#endif

struct property_access {
    typedef enum type {
        r = 1,  // read
        w = 2,  // write
        rw = 3  // read-write
    };
};

namespace property_base {
    template<class type> struct property_write ;
}

namespace property_operators {
    template<class self_type, class property_type> struct string {
        // +=
        property_type operator+=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() + val;
            self.set( new_val);
            return new_val;
        }
    };

    template<class self_type, class property_type> struct flag {
        // |=, &=
        property_type operator|=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() | val;
            self.set( new_val);
            return new_val;
        }
        property_type operator&=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() & val;
            self.set( new_val);
            return new_val;
        }
    };

    template<class self_type, class property_type> struct number {
        // +=, -=, *=, /=
        // ++, --

        property_type operator+=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() + val;
            self.set( new_val);
            return new_val;
        }
        property_type operator-=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() - val;
            self.set( new_val);
            return new_val;
        }
        property_type operator*=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() * val;
            self.set( new_val);
            return new_val;
        }
        property_type operator/=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() / val;
            self.set( new_val);
            return new_val;
        }

        self_type & operator++() {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() + 1;
            self.set( new_val);
            return self;
        }
        property_type operator++(int) {
            self_type & self = static_cast<self_type&>(*this);
            property_type old_val = self.get() ;
            self.set( old_val + 1);
            return old_val;
        }

        self_type & operator--() {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() - 1;
            self.set( new_val);
            return self;
        }
        property_type operator--(int) {
            self_type & self = static_cast<self_type&>(*this);
            property_type old_val = self.get() ;
            self.set( old_val - 1);
            return old_val;
        }

        // FIXME perhaps in the future I will allow only | and & for flags
        // |=, &=
        property_type operator|=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() | val;
            self.set( new_val);
            return new_val;
        }
        property_type operator&=(const property_type & val) {
            self_type & self = static_cast<self_type&>(*this);
            property_type new_val = self.get() & val;
            self.set( new_val);
            return new_val;
        }
    };

    template<class type, class self_type> struct operator_base {};
    template<class self_type> struct operator_base<types::int64,self_type> 
        : number < self_type, types::int64 > {};
    template<class self_type> struct operator_base<int,self_type> 
        : number < self_type, int > {};
    template<class self_type> struct operator_base<egui::string,self_type> 
        : string< self_type, egui::string > {};
}

namespace property_base {

    template<class type> struct getter_ptr {
        getter_ptr(const type & val) : val(val) {}

        const type *operator->() const { return &val; }
    private:
        type val;
    };

    template<class type> struct property_read ;
    template<class type> inline void do_set_getter(property_read<type> & val, boost::function0<type> f ) ; 

    template<class type> struct property_read {
        operator type() const { return get(); }
        type get() const { return getter(); }

        // just in case you want to call a const method on the result
        getter_ptr<type> operator->() const { return getter(); }
    private:
        template<class other_type> friend inline void do_set_getter(property_read<other_type> &, boost::function0<other_type> f );
        boost::function0< type  > getter;
    };
    template<class type> inline void do_set_getter(property_read<type> & val, boost::function0<type> f ) {
        val.getter = f;
    }



    template<class type> struct property_write ;
    template<class type> inline void do_set_setter(property_write<type> & val, boost::function1<void, const type&> f ) ; 

    // here, care about operators!
    template<class type> struct property_write {
        void set(const type& val) {
            setter(val);
        }
        void operator=(const type & val) {
            setter(val);
            return val;
        }
    private:
        template<class other_type> friend inline void do_set_setter(property_write<other_type> & val, boost::function1<void, const other_type&> f ) ; 
        boost::function1< void, const type& > setter;
    };
    template<class type> inline void do_set_setter(property_write<type> & val, boost::function1<void, const type&> f ) {
        val.setter = f;
    }






    template<class type, class param, int have_read, int have_write> struct property_one_arg ;

    template<class type, class param, int have_read, int have_write> struct property_one_arg_holder {
        typedef property_one_arg<type,param,have_read,have_write> property_type;
        property_one_arg_holder(property_type * self, const param& arg) : self(self), arg(arg) {}

        operator type() const {
            // FIXME - see if this affects compile time
            // BOOST_STATIC_ASSERT(have_read); 
            return self->getter(arg);
        }

        const type& operator=(const type & val) {
            // FIXME - see if this affects compile time
            // BOOST_STATIC_ASSERT(have_write); 
            self->setter(arg, val);
            return val;
        }
    private:
        property_type* self;
        param arg;
    };

    
    template<class type, class param, int have_read, int have_write> struct property_one_arg;
//    template<class type, class param, int have_read, int have_write> inline void do_set_getter(
  //      property_one_arg<type,param,have_read,have_write> & val, boost::function1<type,param> f ) ;
//    template<class type, class param, int have_read, int have_write, class p5, class p6> inline void do_set_setter(
  //      property_one_arg<type,param,have_read,have_write> & val, boost::function2<void,p5,p6 > f ) ;

    template<class type, class param, int have_read, int have_write> struct property_one_arg {
        typedef type value_type;
        const property_one_arg_holder<type,param,have_read,have_write> operator()(const param & arg) const { 
            return property_one_arg_holder<type,param,have_read,have_write>( const_cast<property_one_arg*>(this) ,arg);
        }
        property_one_arg_holder<type,param,have_read,have_write> operator()(const param & arg) { 
            return property_one_arg_holder<type,param,have_read,have_write>(this,arg);
        }
    private:
//        template<class p1,class p2, int p3, int p4> friend inline void do_set_getter(
  //          property_one_arg<p1,p2,p3,p4> & val, boost::function1<p1,p2> f ) ;
       
//        template<class p1,class p2, int p3, int p4, class p5, class p6> friend inline void do_set_setter(
  //          property_one_arg<p1,p2,p3,p4> & val, boost::function2<void,p5,p6 > f ) ;
    public:
        boost::function1< type , param > getter;
        boost::function2< void, const param&, const type& > setter;
    };

    template<class type, class param, int have_read, int have_write> inline void do_set_getter(
            property_one_arg<type,param,have_read,have_write> & val, boost::function1<type,param> f ) {
        val.getter = f;
    }
    template<class type, class param, int have_read, int have_write,class p5, class p6> inline void do_set_setter(
            property_one_arg<type,param,have_read,have_write> & val, boost::function2<void,p5,p6 > f ) {
        val.setter = f;
    }





    template<os::type property_os, class base> struct only_for_os {};

#if EGUI_OS >= 4000
    template<class base> struct only_for_os<os::win_vista, base> : base {};
#endif

#if EGUI_OS >= 3000
    template<class base> struct only_for_os<os::win_xp_sp2, base> : base {};
#endif

#if EGUI_OS >= 2000
    template<class base> struct only_for_os<os::win_xp, base> : base {};
#endif

#if EGUI_OS >= 1000
    template<class base> struct only_for_os<os::win_2k_sp4, base> : base {};
#endif

#if EGUI_OS >= 0
    template<class base> struct only_for_os<os::win_2k, base> : base {};
#endif


}


/** 
    represents a window property - no arguments passed to the property
*/
struct property
{
    template<class type, class base_type = void_, os::type property_os = os::win_2k > struct rw 
        // we derive from base_type first, so that code-completion works (it's easy for the compiler to parse the base_type class)
        : base_type
        , property_base::only_for_os< property_os, property_base::property_read<type> >
        , property_base::only_for_os< property_os, property_base::property_write<type> >
        , property_operators::operator_base< type, rw<type,base_type,property_os> >
    {
        const type & operator=(const type & val) {
            property_base::property_write<type>::set(val);
            return val;
        }
    };

    template<class type, class base_type = void_, os::type property_os = os::win_2k > struct r 
        : base_type
        , property_base::only_for_os< property_os, property_base::property_read<type> > 
    {};

    template<class type, class base_type = void_, os::type property_os = os::win_2k > struct w
        : base_type
        , property_base::only_for_os< property_os, property_base::property_write<type> >
    {
        const type & operator=(const type & val) {
            property_base::property_write<type>::set(val);
            return val;
        }
    };
};

/** 
    represents a window property - no arguments passed to the property
*/
struct property_one_arg
{
    template<class type, class param, class base_type = void_, os::type property_os = os::win_2k > struct rw 
        : base_type
        , property_base::only_for_os< property_os, property_base::property_one_arg<type, param, 1, 1> >
    {};

    template<class type, class param, class base_type = void_, os::type property_os = os::win_2k > struct r 
        : base_type
        , property_base::only_for_os< property_os, property_base::property_one_arg<type, param, 1, 0> >
    {};

    template<class type, class param, class base_type = void_, os::type property_os = os::win_2k > struct w
        : base_type
        , property_base::only_for_os< property_os, property_base::property_one_arg<type, param, 0, 1> >
    {};
};

}

#endif

