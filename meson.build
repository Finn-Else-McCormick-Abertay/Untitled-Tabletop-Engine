project(
    'untitled_tabletop_engine',
    'cpp', default_options: ['cpp_std=c++17'],
    version: '0.0.1'
)

# Program source
shared_src = []
shared_include_dir = 'src/shared'

client_src = [
    'src/client/client_main.cpp',
    'src/client/systems/impl/window_system_impl_sdl2.cpp',
    'src/client/systems/impl/render_system_impl_opengl3.cpp',
    'src/client/systems/impl/input_system_impl_sdl2.cpp',
]
client_include_dirs = [ 'src/client' ]
client_pch_path = 'pch/client_pch.h'

server_src = [
    'src/server/server_main.cpp'
]
server_include_dir = 'src/server'
server_pch_path = 'pch/server_pch.h'

# ImGui source
imgui_src = [
    'imgui/imgui.cpp', 'imgui/imgui_demo.cpp', 'imgui/imgui_draw.cpp', 'imgui/imgui_tables.cpp', 'imgui/imgui_widgets.cpp',
    'imgui/backends/imgui_impl_sdl2.cpp', 'imgui/backends/imgui_impl_opengl3.cpp'
]
imgui_include_dirs = ['imgui', 'imgui/backends']

# Dependencies
sdl2 = dependency('sdl2')
#sdl2_main = dependency('sdl2main')
opengl = dependency('gl')
glew = dependency('glew')
#glm = dependency('glm')
lua = dependency('lua', version:'>=5.4')
enet = dependency('libenet')

# Copy assets to build directory
run_target('assets', command: ['scripts/copy_assets.cmd'])

executable('client',
    sources: shared_src + client_src + imgui_src,
    include_directories: [ shared_include_dir ] + client_include_dirs + imgui_include_dirs,
    cpp_pch: client_pch_path,
    #win_subsystem: 'windows',
    dependencies: [ sdl2, opengl, glew, lua, enet ]
)
