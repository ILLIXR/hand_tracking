set(GPU_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/gpu_service.cc
    ${CMAKE_CURRENT_LIST_DIR}/gpu_service.h
    ${CMAKE_CURRENT_LIST_DIR}/graph_support.h
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_storage_image_frame.cc
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_storage_image_frame.h
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_storage.cc
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_storage.h
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_format.cc
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_format.h
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer.cc
    ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer.h

)

target_sources(${PLUGIN_NAME} PRIVATE
               ${GPU_SOURCES}
)
if(HT_ENABLE_GPU)
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/gpu_shared_data_internal.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gpu_shared_data_internal.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_base.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_context.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_context.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_context_egl.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_context_internal.h
                   ${CMAKE_CURRENT_LIST_DIR}/attachments.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_thread_collector.h
                   ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_multi_pool.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gpu_buffer_multi_pool.h
                   ${CMAKE_CURRENT_LIST_DIR}/frame_buffer_view.h
                   ${CMAKE_CURRENT_LIST_DIR}/image_frame_view.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_buffer.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_buffer.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_view.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_view.h
                   ${CMAKE_CURRENT_LIST_DIR}/gpu_shared_data_internal.h
                   ${CMAKE_CURRENT_LIST_DIR}/multi_pool.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_buffer_pool.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_texture_buffer_pool.h
                   ${CMAKE_CURRENT_LIST_DIR}/reusable_pool.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_calculator_helper.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_calculator_helper.h
                   ${CMAKE_CURRENT_LIST_DIR}/shader_util.cc
                   ${CMAKE_CURRENT_LIST_DIR}/shader_util.h
                   ${CMAKE_CURRENT_LIST_DIR}/gl_simple_shaders.cc
                   ${CMAKE_CURRENT_LIST_DIR}/gl_simple_shaders.h
    )
endif()