namespace egui {

/** 
@page todo_s TODOs




all controls
properties -> allow operators, also for flags



FORMS MODULE allow adding existing forms like open_form, save_form, etc.



I can allow property-like behavior of calling a member function
like list->item(1)->whatever = 5;
should be able to have somehow getter and then setter (for instance, I could cache the getter)







DOCS- wanna help? you're most welcome!
DOCS - convention - every types::type, when used within a class, it's class::type_type
     like: rebar_band = rebar::band_type



********* IMPL -> tree tooltip toolbar rebar 












how do i end dialog when a button is pressed?






- weak_wnd




- 

- i need to have a module that will allow dealing with raw_hwnd(). by default, this is all hidden
  - this besides allowing access to raw_hwnd, will also allow subclassing other windows (not our own), so that we can 
    easily reference them as well
  - timeframe 

- events 
  - handle all events a window exposes - make a class for that


- find_by_hwnd - we'll search by raw_hwnd - whichh is an internal method


  - put on that site with lots of mfc examples, etc





in order to minimize the code that i write for parsing events - etc, some stuff will not be parsed.
WHAT CAN BE DEFINED AS A FUNCTION, IMPLEMENTED SOMEWHERE ELSE, WILL BE DONE SO (as oppposed to do some parsing and define it inline)









*******
wnd<rebar> w = new_(parent);

-> I can have new_<type>(...) and new_(...);
for the second form - allow wnd<type> to be constructed from new_(...) -> new_(...) is a function returning a holder of values)
-->up to 10 arguments
"wnd<> w = new_(...)" => this throws - you need to specify the type of window you want to create

the window class  - must NOT be copyable

flag classes, properties!
can say x.text += "something";

wnd<> w = new_<some_name>(...);
every time you use w->, it checks that the window is valid
the difference between 

weak_wnd<> - for storing pointer to parent or so.

to delete -> delete_<>

RAII - you get what you ask for = one-window = one-c++-instance.
function is_valid(w)
and use_even_if_not_valid(w)->whatever() (just in case you need to release its resources or whatever)

********explain why not local variables- what if the user destroys one?.

also - when out of scope, if it's a form, see what to do.
wnd<> f = new_<some_form>(...);
// how do i keep this on screen?
(taht is, after scope is exited)




control versus form - only for a form, you can access its children. a control can be a form.




At one time, you can end up with multiple wnd<> pointers


About multiple wnd<> pointers – a c++ exception, as opposed to a possible crash.
The weak_wnd<> class














Dealing with windows – the basics

When dealing with windows, you’ll always use the wnd<> or the weak_wnd<> templated classes:
•	wnd<> - represents a shared (ref counted) pointer to a window
•	weak_wnd<> - represents a weak pointer to a window

The wnd<>/weak_wnd<> classes have one optional argument – the window type. This is pretty much what you’d expect: by default, it’s window_base. Or it can be a window class: text, label, rebar, edit_box, etc.

Usually you’ll always deal with wnd<> objects. Internally, each such object maintains a ref counted pointer to the C++ instance corresponding to the on-the-screen object. When you need to avoid circular references, you can use weak_wnd<>.



wnd<> and try_wnd<> -> need to work for raw pointers as well - in case we use them within our member methods
self() - cannot be used in the constructor
--- depending on what you want to do, you can do it on on_create()




I will have a solution that contains ALL PROJECTS, and allows compilation debug/release/unicode debug/unicode release
after that, depending on what the user includes, have #pragma comment lib


commctrl -> don't have _WINNT blabla. WinXP and WinVista.

creation of a window - if rect is not specified = all parent's scrren




::LoadAccelerators - try with the closest form; if not, the higher form until reaching the top.


tab control: one_dialog_per_tab
have property : "count" , like tab->count = 5; in this case, I will take the last added form, and copy it
in as many pieces as needed. if at this time tab->count = 0 -> exception will be thrown
probably i will need to have a way to clone a form and/or control for this matter
this needs to work EVEN IF THERE'S NO DEFAULT constructor
--> need to copy all properties - in other words, properties need to be somehow copy constructible TOTHINK!!!

*/

}
