set(TARGET pdfparamGRV_sea)
add_library(${TARGET} MODULE GRV_sea_PdfParam.cc)
target_link_libraries(${TARGET} PRIVATE xfitter)
install(TARGETS ${TARGET} DESTINATION ${DEST_MODULE})
