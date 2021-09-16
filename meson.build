project('librippr', 'c', version : '1.0')

core_inc = include_directories('src')

librippr_deps = [
    dependency('xcb')
]

librippr_srcs = [
    'src/librippr.c'
]

test_srcs = [
    'test/main.c'
]

librippr = library(
    'rippr', 
    librippr_srcs, 
    dependencies : librippr_deps
)

executable(
    'rippr_test', 
    test_srcs, 
    include_directories : core_inc, 
    link_with : librippr
)