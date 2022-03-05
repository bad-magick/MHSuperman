// IDD_convert
// 
// Automatically generated - DO NOT EDIT
#ifndef form_resource_convert_h_JT_egui
#define form_resource_convert_h_JT_egui

#include "resource.h"
#include "egui/core/wnd.hpp"
#include "egui/forms/detail/form_event.hpp"
//#include "egui_resource_menus.hpp"
#include <map>


#include <egui/controls/button.hpp>
#include <egui/controls/edit.hpp>

namespace form_resource {
using namespace egui;

struct convert : public ::egui::form {

static int form_id() { return IDD_convert; }

void on_initialize();
void on_child_notify(ev::notify& evt);


protected:

struct ok_ {};
struct usd_ {};
struct eur_ {};

virtual void on_clicked(button::ev::clicked&, ok_) {}
virtual void on_focus(button::ev::focus&, ok_) {}
virtual void on_focus(edit::ev::focus&, usd_) {}
virtual void on_change(edit::ev::change&, usd_) {}
virtual void on_update(edit::ev::update&, usd_) {}
virtual void on_max_text(edit::ev::max_text&, usd_) {}
virtual void on_focus(edit::ev::focus&, eur_) {}
virtual void on_change(edit::ev::change&, eur_) {}
virtual void on_update(edit::ev::update&, eur_) {}
virtual void on_max_text(edit::ev::max_text&, eur_) {}

// FIXME access needs to be customizable
public:

wnd<button> ok;
wnd<edit> usd;
wnd<edit> eur;

private:
typedef ::egui::form_func_base< convert > func_base;
typedef boost::shared_ptr< func_base > form_func_ptr;
typedef std::map< ::egui::typeinfo_holder, form_func_ptr > type_to_event_coll;
typedef std::map< ::egui::wnd<>, type_to_event_coll > notify_coll;
notify_coll m_notifications;

};

}

#endif
