// IDD_convert
// 
// Automatically generated - DO NOT EDIT

#include "convert_form_resource.h"

namespace form_resource {

void convert :: on_initialize() {

ok = wnd_cast<button>( child_by_id(1));
usd = wnd_cast<edit>( child_by_id(IDC_usd));
eur = wnd_cast<edit>( child_by_id(IDC_eur));


{ type_to_event_coll & notif = m_notifications[ ok];
  { egui::form_func<convert,button::ev::clicked,ok_>::func f = &convert::on_clicked;
    egui::form_func<convert,button::ev::clicked,ok_> * func = new egui::form_func<convert,button::ev::clicked,ok_>(this,f); 

    notif[ typeid(button::ev::clicked) ] = form_func_ptr(func); }
  { egui::form_func<convert,button::ev::focus,ok_>::func f = &convert::on_focus;
    egui::form_func<convert,button::ev::focus,ok_> * func = new egui::form_func<convert,button::ev::focus,ok_>(this,f); 

    notif[ typeid(button::ev::focus) ] = form_func_ptr(func); }} 

{ type_to_event_coll & notif = m_notifications[ usd];
  { egui::form_func<convert,edit::ev::focus,usd_>::func f = &convert::on_focus;
    egui::form_func<convert,edit::ev::focus,usd_> * func = new egui::form_func<convert,edit::ev::focus,usd_>(this,f); 

    notif[ typeid(edit::ev::focus) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::change,usd_>::func f = &convert::on_change;
    egui::form_func<convert,edit::ev::change,usd_> * func = new egui::form_func<convert,edit::ev::change,usd_>(this,f); 

    notif[ typeid(edit::ev::change) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::update,usd_>::func f = &convert::on_update;
    egui::form_func<convert,edit::ev::update,usd_> * func = new egui::form_func<convert,edit::ev::update,usd_>(this,f); 

    notif[ typeid(edit::ev::update) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::max_text,usd_>::func f = &convert::on_max_text;
    egui::form_func<convert,edit::ev::max_text,usd_> * func = new egui::form_func<convert,edit::ev::max_text,usd_>(this,f); 

    notif[ typeid(edit::ev::max_text) ] = form_func_ptr(func); }} 

{ type_to_event_coll & notif = m_notifications[ eur];
  { egui::form_func<convert,edit::ev::focus,eur_>::func f = &convert::on_focus;
    egui::form_func<convert,edit::ev::focus,eur_> * func = new egui::form_func<convert,edit::ev::focus,eur_>(this,f); 

    notif[ typeid(edit::ev::focus) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::change,eur_>::func f = &convert::on_change;
    egui::form_func<convert,edit::ev::change,eur_> * func = new egui::form_func<convert,edit::ev::change,eur_>(this,f); 

    notif[ typeid(edit::ev::change) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::update,eur_>::func f = &convert::on_update;
    egui::form_func<convert,edit::ev::update,eur_> * func = new egui::form_func<convert,edit::ev::update,eur_>(this,f); 

    notif[ typeid(edit::ev::update) ] = form_func_ptr(func); }
  { egui::form_func<convert,edit::ev::max_text,eur_>::func f = &convert::on_max_text;
    egui::form_func<convert,edit::ev::max_text,eur_> * func = new egui::form_func<convert,edit::ev::max_text,eur_>(this,f); 

    notif[ typeid(edit::ev::max_text) ] = form_func_ptr(func); }} 


form::on_initialize();
}

void convert :: on_child_notify(ev::notify& evt) {
  type_to_event_coll & type_to_evt = m_notifications[ evt.sender];
  form_func_ptr f = type_to_evt[ typeid(evt) ];
  if ( f)
    f->call(evt);
}

}


