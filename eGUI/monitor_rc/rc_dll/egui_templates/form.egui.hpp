// $form_id$
// 
// Automatically generated - DO NOT EDIT
#ifndef form_resource_$form$_h_JT_egui
#define form_resource_$form$_h_JT_egui

#include "resource.h"
#include "egui/core/wnd.hpp"
#include "egui/forms/detail/form_event.hpp"
//#include "egui_resource_menus.hpp"
#include <map>

$control_includes$

namespace form_resource {
using namespace egui;

struct $form$ : public ::egui::form {

static int form_id() { return $form_id$; }

void on_initialize();
void on_child_notify(ev::notify& evt);


protected:
$control_classes$
$notifications$

// FIXME access needs to be customizable
public:
$control_declarations$

private:
typedef ::egui::form_func_base< $form$ > func_base;
typedef boost::shared_ptr< func_base > form_func_ptr;
typedef std::map< ::egui::typeinfo_holder, form_func_ptr > type_to_event_coll;
typedef std::map< ::egui::wnd<>, type_to_event_coll > notify_coll;
notify_coll m_notifications;

};

}

#endif
