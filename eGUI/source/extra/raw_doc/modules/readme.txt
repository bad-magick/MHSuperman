see what i have from win32gui






You don't need to #include <windows.h> in your code
- any of the headers of EGUI does not include this
  - have something like detail/impl.h - only included in implementation

- dealing with items - completely different from implementation:
OLD :
rb->add_band( rebar_band_info()
    .style(RBBS_BREAK | RBBS_CHILDEDGE | RBBS_GRIPPERALWAYS)
    .width(170)
    .text("MyCombo ")
    .child( create_wnd<combo_box>(rb)) );


NEW (see "Put that code completion to work"):
rebar_band r;
r.style = r.style.break_ | r.style.child_edge;
r = rb->get_band(idx);
// i need to know what changed
r.style |= whatever;

RATIONALE: it's pointless to care about efficiency of setting a property/etc when it comes to GUI - always, drawing what comes of the result of that property is actually important.

get/set functions - have the same name - x.text(), x.text( "something"); - actually, use properties x.text = "blabla", x.text += "x"; etc.

I'll have a parser 
- parse windows files, and get the defines from them. - parsing windows files.txt

Put that code-completion to work:
struct container {
    struct style_type {
        static const bool x = true;
        static const int count = 5;
        int val;
    };
    style_type style;
};

int main() {
    container c;
    c.style += c.style.count;
}






MODULAR - turn on/off modules - EASY
SCHELETRON needs to be very small

EVENTS - WAY EASIER THAN NOW
EVENTS - A SEPARATE MODULE

I WILL HAVE THE CORE MODULE AS WELL






don't care too much about thread-safety
- not more than needed

extending an existing window class -- should be easy
- no more event_handler thingy
- no more advanced subclassing

have - on_create/on_destroy --> catch events and call them


The events will be completely separated from the rest
-- events - only one argument which can be ignore_event_arg&

that is, it's a completely different pluggable module - if you want it, use it, otherwise not

need to catch when controls are created
-- see if i can access the dialog children from the constructor of a dialog class
-- easy way to enumerate children



can even have default arguments, like --- not for now
window<caption> w = ...;
*w = "test";

use boost.reflection
use boost 1.34.1

should be able to make local window variables, like:
caption c(parent);
also - automatically know if a variable is created on the stack or not
-- create_wnd -> will derive from dynamic_window<type> which specifies that this is dynamic
-- when variable goes out of scope, destroy window


I will not have the crap of find_wnd<> stuff
-- i will have a simpler version


event subscribers - there must be a way so that when 
object is deleted, all the subscribers are destroyed
however, while an object exists, the subscribesr must exist as well - need mechanism for that.


i should allow for a subscriber to an event/subscriber to multiple events to work easily.
also, when an event is triggered, need to catch it, and send it to our subscriber(s) as well
-- need to have event_handler for a certain form, which receives events from controls as well





the new MFC - does it fully support tabs/dockability? (like, putting a control on a tab)




when dealing with item data - like a list item or so (modifying its settings).
Need to find a way to much more easily deal with this  -unlike win32gui. 
It should still be property related - don't expose the fact that multiple things at once are manipulated.
(dealing with flags)
-----> besides that, i need to have default flags
w->style |= w->style.something;
even more, styles can be inherited; for instance, button has more styles - will inherit existing ones + new ones
(most likely overload the style property)



allow for MVC - later!


simple concept:
form and control -- taht's all (no dialog)


easy way to do refactoring - that is, set propertise at runtime!!!




when i start the first window, the events handler needs to be inplace


INTEGRATE WITH VC2005/VC2008

