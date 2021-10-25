# Source files (except the main for the executable):
set(origin_src
  main.c
  species.c
  ivector.c
  specieslist.c
  utils.c
  graph.c
)

# Compile the executable
add_executable(origin ${origin_src})

target_link_libraries(origin ${GSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})

# How and what to install
install(TARGETS origin RUNTIME DESTINATION bin)

