
REM Tutorial01_HelloTriangle
glslang -V -S vert -o Tutorial01_HelloTriangle/vertex.450core.spv Tutorial01_HelloTriangle/vertex.450core.glsl
glslang -V -S frag -o Tutorial01_HelloTriangle/fragment.450core.spv Tutorial01_HelloTriangle/fragment.450core.glsl

REM Tutorial02_Tessellation
glslang -V -S vert -o Tutorial02_Tessellation/vertex.450core.spv Tutorial02_Tessellation/vertex.450core.glsl
glslang -V -S frag -o Tutorial02_Tessellation/fragment.450core.spv Tutorial02_Tessellation/fragment.450core.glsl
glslang -V -S tesc -o Tutorial02_Tessellation/tesscontrol.450core.spv Tutorial02_Tessellation/tesscontrol.450core.glsl
glslang -V -S tese -o Tutorial02_Tessellation/tesseval.450core.spv Tutorial02_Tessellation/tesseval.450core.glsl

REM Tutorial03_Texturing
glslang -V -S vert -o Tutorial03_Texturing/vertex.450core.spv Tutorial03_Texturing/vertex.450core.glsl
glslang -V -S frag -o Tutorial03_Texturing/fragment.450core.spv Tutorial03_Texturing/fragment.450core.glsl

REM Tutorial05_RenderTarget
glslang -V -S vert -o Tutorial05_RenderTarget/vertex.450core.spv Tutorial05_RenderTarget/vertex.450core.glsl
glslang -V -S frag -o Tutorial05_RenderTarget/fragment.450core.spv Tutorial05_RenderTarget/fragment.450core.glsl

REM Tutorial06_MultiContext
glslang -V -S vert -o Tutorial06_MultiContext/vertex.450core.spv Tutorial06_MultiContext/vertex.450core.glsl
glslang -V -S frag -o Tutorial06_MultiContext/fragment.450core.spv Tutorial06_MultiContext/fragment.450core.glsl
glslang -V -S geom -o Tutorial06_MultiContext/geometry.450core.spv Tutorial06_MultiContext/geometry.450core.glsl

REM Tutorial07_Array
glslang -V -S vert -o Tutorial07_Array/vertex.450core.spv Tutorial07_Array/vertex.450core.glsl
glslang -V -S frag -o Tutorial07_Array/fragment.450core.spv Tutorial07_Array/fragment.450core.glsl

REM Tutorial08_Compute
glslang -V -S comp -o Tutorial08_Compute/compute.spv Tutorial08_Compute/compute.glsl

REM Tutorial10_Instancing
glslang -V -S vert -o Tutorial10_Instancing/vertex.450core.spv Tutorial10_Instancing/vertex.450core.glsl
glslang -V -S frag -o Tutorial10_Instancing/fragment.450core.spv Tutorial10_Instancing/fragment.450core.glsl

pause