add_library(crash SHARED
	boolean.c
	exec.c
	float.c
	integer.c
	memory.c
	pointer.c
	string.c
	user.c
	utils.c
)

target_include_directories(crash PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/private)

install(TARGETS crash DESTINATION /usr/lib)