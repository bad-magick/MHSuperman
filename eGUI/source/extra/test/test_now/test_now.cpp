// test_now.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "test_now.h"
#include "egui/core/wnd.hpp"
#include "egui/core/detail/log.hpp"
#include "egui/controls/all.hpp"
#include "egui/main/main.hpp"
using namespace egui;

struct test_event : new_event<test_event> {
    int val;
    test_event(int i) : val(i) {}
};

struct about : form {
    static int form_id() { return IDD_ABOUTBOX; }

    void on_notify(ev::notify& e) {
        LEGUI_ << "******* on notify " << type_name(e);
    }

    void on_mouse_move(ev::mouse_move& ) {
        LEGUI_ << "on mousemove" ;
    }

    void on_activate(ev::activate&) {
        LEGUI_ << "on activate" ;
    }

    struct events_type : form::events_type {
        event_handler<test_event> on_test;
    } events;
};

void change(edit::ev::change& ) {
    LEGUI_ << "edit_change " ;
}
void focus(edit::ev::focus &f ) {
    LEGUI_ << "edit_focus " << f.received;
}

void test(test_event & t) {
    LEGUI_ << "test " << t.val;
}

struct editer : non_intrusive_handler {
    void on_new_window_create(wnd<> w) {
        if ( wnd<edit> e = try_wnd_cast<edit>( w))
        {
            e->events.on_change += change;
            e->events.on_focus += focus;
        }
    }
};

void egui::main(const main_args&) {
  wnd<form> f = new_(); 
  f->add_child<label>( new_("Hello world"));
  f->wait_for( ev::destroy() );

    msg_box<mb::ok>("dd");
    window_top::add_non_intrusive_handler( editer() );
    wnd<about> w = new_<about>("test");

    window_top::register_event_handler<about>(&about::events_type::on_test);
    w->wait_for( ev::destroy() );
    msg_box<mb::ok>("dd");
}

