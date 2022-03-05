// IDD_login
// 
// Automatically generated - DO NOT EDIT

#include "login_form_resource.h"

namespace form_resource {

void login :: on_initialize() {

ok = wnd_cast<button>( child_by_id(1));
username = wnd_cast<edit>( child_by_id(IDC_username));
passw = wnd_cast<edit>( child_by_id(IDC_passw));


{ type_to_event_coll & notif = m_notifications[ ok];
  { egui::form_func<login,button::ev::clicked,ok_>::func f = &login::on_clicked;
    egui::form_func<login,button::ev::clicked,ok_> * func = new egui::form_func<login,button::ev::clicked,ok_>(this,f); 

    notif[ typeid(button::ev::clicked) ] = form_func_ptr(func); }
  { egui::form_func<login,button::ev::focus,ok_>::func f = &login::on_focus;
    egui::form_func<login,button::ev::focus,ok_> * func = new egui::form_func<login,button::ev::focus,ok_>(this,f); 

    notif[ typeid(button::ev::focus) ] = form_func_ptr(func); }} 

{ type_to_event_coll & notif = m_notifications[ username];
  { egui::form_func<login,edit::ev::focus,username_>::func f = &login::on_focus;
    egui::form_func<login,edit::ev::focus,username_> * func = new egui::form_func<login,edit::ev::focus,username_>(this,f); 

    notif[ typeid(edit::ev::focus) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::change,username_>::func f = &login::on_change;
    egui::form_func<login,edit::ev::change,username_> * func = new egui::form_func<login,edit::ev::change,username_>(this,f); 

    notif[ typeid(edit::ev::change) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::update,username_>::func f = &login::on_update;
    egui::form_func<login,edit::ev::update,username_> * func = new egui::form_func<login,edit::ev::update,username_>(this,f); 

    notif[ typeid(edit::ev::update) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::max_text,username_>::func f = &login::on_max_text;
    egui::form_func<login,edit::ev::max_text,username_> * func = new egui::form_func<login,edit::ev::max_text,username_>(this,f); 

    notif[ typeid(edit::ev::max_text) ] = form_func_ptr(func); }} 

{ type_to_event_coll & notif = m_notifications[ passw];
  { egui::form_func<login,edit::ev::focus,passw_>::func f = &login::on_focus;
    egui::form_func<login,edit::ev::focus,passw_> * func = new egui::form_func<login,edit::ev::focus,passw_>(this,f); 

    notif[ typeid(edit::ev::focus) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::change,passw_>::func f = &login::on_change;
    egui::form_func<login,edit::ev::change,passw_> * func = new egui::form_func<login,edit::ev::change,passw_>(this,f); 

    notif[ typeid(edit::ev::change) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::update,passw_>::func f = &login::on_update;
    egui::form_func<login,edit::ev::update,passw_> * func = new egui::form_func<login,edit::ev::update,passw_>(this,f); 

    notif[ typeid(edit::ev::update) ] = form_func_ptr(func); }
  { egui::form_func<login,edit::ev::max_text,passw_>::func f = &login::on_max_text;
    egui::form_func<login,edit::ev::max_text,passw_> * func = new egui::form_func<login,edit::ev::max_text,passw_>(this,f); 

    notif[ typeid(edit::ev::max_text) ] = form_func_ptr(func); }} 


form::on_initialize();
}

void login :: on_child_notify(ev::notify& evt) {
  type_to_event_coll & type_to_evt = m_notifications[ evt.sender];
  form_func_ptr f = type_to_evt[ typeid(evt) ];
  if ( f)
    f->call(evt);
}

}


