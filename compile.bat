@echo vulkan sdk's location:
@echo %VULKAN_SDK%
@echo start compiling

@if not exist "src/Shaders/output" md "src/Shaders/output"
%VULKAN_SDK%/Bin/glslc.exe src/Shaders/shader.vert -o src/Shaders/output/vert.spv
%VULKAN_SDK%/Bin/glslc.exe src/Shaders/shader.frag -o src/Shaders/output/frag.spv

@echo finish compiling