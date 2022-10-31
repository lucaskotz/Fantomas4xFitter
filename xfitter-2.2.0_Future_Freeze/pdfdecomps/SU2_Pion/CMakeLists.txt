set(TARGET pdfdecompSU2_Pion)
add_library(${TARGET} MODULE SU2_PionPdfDecomposition.cc)
target_link_libraries(${TARGET} PRIVATE xfitter)
install(TARGETS ${TARGET} DESTINATION ${DEST_MODULE})
