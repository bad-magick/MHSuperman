// IDD_login
// 
// Automatically generated - DO NOT EDIT
#ifndef form_resource_login_h_JT_egui
#define form_resource_login_h_JT_egui

#include "resource.h"
#include "egui/core/wnd.hpp"
#include "egui/forms/detail/form_event.hpp"
//#include "egui_resource_menus.hpp"
#include <map>


#include <egui/controls/button.hpp>
#include <egui/controls/edit.hpp>

namespace form_resource {
using namespace egui;

struct login : public ::egui::form {

static int form_id() { return IDD_login; }

void on_initialize();
void on_child_notify(ev::notify& evt);


protected:

struct ok_ {};
struct username_ {};
struct passw_ {};

virtual void on_clicked(button::ev::clicked&, ok_) {}
virtual void on_focus(button::ev::focus&, ok_) {}
virtual void on_focus(edit::ev::focus&, username_) {}
virtual void on_change(edit::ev::change&, username_) {}
virtual void on_update(edit::ev::update&, username_) {}
virtual void on_max_text(edit::ev::max_text&, username_) {}
virtual void on_focus(edit::ev::focus&, passw_) {}
virtual void on_change(edit::ev::change&, passw_) {}
virtual void on_update(edit::ev::update&, passw_) {}
virtual void on_max_text(edit::ev::max_text&, passw_) {}

// FIXME access needs to be customizable
public:

wnd<button> ok;
wnd<edit> username;
wnd<edit> passw;

private:
typedef ::egui::form_func_base< login > func_base;
typedef boost::shared_ptr< func_base > form_func_ptr;
typedef std::map< ::egui::typeinfo_holder, form_func_ptr > type_to_event_coll;
typedef std::map< ::egui::wnd<>, type_to_event_coll > notify_coll;
notify_coll m_notifications;

};

}

#endif
