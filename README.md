## RAOE Camera

A simple camera library for video games. Written in cpp20. Based on the absolutely fantastic Rust library [Dolly](https://github.com/h3r2tic/dolly)

Camera rigs are engine agnostic and only provide a view transform for you to use.  

This is an open sourced module from my personal game engine (Roy Awesome's Open Engine).

### Dependencies

* A C++ 20 compiler
* [GLM](https://github.com/g-truc/glm)
* [catch2](https://github.com/catchorg/Catch2) (for tests)

Note: Using the CMake Integration will automatically acquire glm using [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake).

### Usage
Simply include this folder with cmake and depend on `raoe::camera`.  

```cpp
raoe::camera::controller look_at_controller;

look_at_controller.with<raoe::camera::yaw_pitch>(45.0f, 45.0f)
                        .with<raoe::camera::arm>(glm::vec3(0, 30, 0))
                        .with<raoe::camera::look_at>(glm::vec3(0, 0, 0));

//in your games update loop:
look_at_controller.update(your_delta_time);

glm::mat4 view_matrix = look_at_controller.view_matrix();
//use this view matrix anywhere you'd use this code.
```

### Credits

A huge shout out to h3r2tic's dolly library, which was used as a basis for this library.  


### License

This project is open source and permissively licensed, under either MIT or Apache 2.0. You may chose either license.

This dual licensing approach provides a few benefits:

* Apache 2.0 provides protection from patent trolling, and reduces license boilerplate
* MIT is compatible with many other open source licenses
* Both licenses have various ecosystems to support them
