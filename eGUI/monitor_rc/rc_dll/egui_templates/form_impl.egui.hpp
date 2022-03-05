// $form_id$
// 
// Automatically generated - DO NOT EDIT

#include "$form$_form_resource.h"

namespace form_resource {

void $form$ :: on_initialize() {
$control_mappings$

$event_mappings$

form::on_initialize();
}

void $form$ :: on_child_notify(ev::notify& evt) {
  type_to_event_coll & type_to_evt = m_notifications[ evt.sender];
  form_func_ptr f = type_to_evt[ typeid(evt) ];
  if ( f)
    f->call(evt);
}

}


