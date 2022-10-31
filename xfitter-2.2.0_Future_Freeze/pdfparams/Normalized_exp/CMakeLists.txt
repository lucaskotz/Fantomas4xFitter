set(TARGET pdfparamNormalized_exp)
add_library(${TARGET} MODULE Normalized_exp_PdfParam.cc)
target_link_libraries(${TARGET} PRIVATE xfitter)
install(TARGETS ${TARGET} DESTINATION ${DEST_MODULE})
