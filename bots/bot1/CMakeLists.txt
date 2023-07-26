
add_library(bot1 MODULE
   bot1.cpp
)

target_compile_definitions(bot1 PUBLIC std_cxx_17)
target_include_directories(bot1 PUBLIC ../include)