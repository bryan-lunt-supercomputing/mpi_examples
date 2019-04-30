
add_executable(star_graph "star_graph.cpp")
target_link_libraries(star_graph PUBLIC m )
target_include_directories(star_graph PUBLIC ${MPI_CXX_INCLUDE_PATH})
target_link_libraries(star_graph PUBLIC ${MPI_CXX_LIBRARIES})


add_executable(dist_graph "disconnected_graph.cpp")
target_link_libraries(dist_graph PUBLIC m )
target_include_directories(dist_graph PUBLIC ${MPI_CXX_INCLUDE_PATH})
target_link_libraries(dist_graph PUBLIC ${MPI_CXX_LIBRARIES})
