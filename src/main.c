#include <pebble.h>


//it is also a C convention to define all or most of your variables at the top.  We can talk about that later, but if you are interested now
//check out this article on "scope" => http://www.tutorialspoint.com/cprogramming/c_scope_rules.htm
Window *my_window;
TextLayer *text_layer;
char output_string[800] = "";

// here we are creating a sctruct called "profile"  
// We then define what it is that makes up a profile.
// in the following code we state that each profile has an integer called "id_number", 
// an integer called "age" and decimal(floating point) value that is called salary
  struct profile {
  int id_number;
  int age;
  char *name;
};



//here is the definition of the "main_window_load" function.  Which is called by the app_event_loop() when the user opens your app.
static void main_window_load(Window *window){

  //now we are going to create a variable that will have the characteristics that we defined above.
  //We are creating a variable called "employee" which has an age, id_number and salary.
  struct profile employee;
  //to access the property of a structure we use what is sometimes called "dot notation"
  //here we are just assigning them hard-coded values, but in a real app, you'd be getting
  //this info from some other data source.
  employee.age = 22;
  employee.id_number = 1;
  employee.name = "Bobby Jo Jim Jr. III";
  
  //now we are going to access those values so that we can plug them into this snprintf statement.
  //snprintf() takes the text we gave it between the quotation marks, and then plugs in the two parameters
  //we give it afterwords into the place holder %s (for string) and %i for integer.
  //I am also using \n which tells snprintf() that I would like it to create a new line right there.
  snprintf(output_string, sizeof(output_string), "Employee name:\n %s \n\nEmployee age:\n %i", employee.name, employee.age);
  
  Layer *window_layer = window_get_root_layer(window);
  text_layer = text_layer_create(GRect(0, 0, 144, 168));
  
  //finally we set our text to be the content of the output_string variable that we initialized at the top of the code
  //and then added data to, by passing it into the snprintf() function.
  text_layer_set_text(text_layer, output_string );
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

//here is the definition for what we want the program to do when the app_event_loop() is broken.  Which will happen when the user leaves the app.
static void main_window_unload(){
   text_layer_destroy(text_layer);
}


// here we have created the initial steps that we want to take place when this code is called from the "main" function
void handle_init(void) {
  my_window = window_create();
  window_set_window_handlers(my_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(my_window, true);
}

// here we are defining the steps that we need our program to take when the user leaves our main window.
// notice that in the "main" function, the call to this code comes after the app_event_loop()
// In our case we are just cleaning house and releasing the memory that we allocated to create the window,
// but you could do anything you like here in addition to that.
void handle_deinit(void) {
 window_destroy(my_window);
}


//START HERE!  <-------------------------------------
//here is the "main" function.  All C programs must have a main function.  This is the humble center of your program.
//all of the definitions for the different functions that are being called in main are given above.  This is because C
//requires that you define a function before it can be called.
//Even though we define the steps above, this is where those functions are actually executed.
//so when a user clicks "select" on your app from their menu, the "main()" function executes all of the functions that you
//tell it to execute, in order.  "The app_event_loop()" function is a built in part of the pebble o.s. and it will keep running
//until the user exits the program.  We'll talk more about the loop when we do animations.
//But if you want more detailed info on app_event_loop() read => http://developer.getpebble.com/docs/c/Foundation/App/#app_event_loop 
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}