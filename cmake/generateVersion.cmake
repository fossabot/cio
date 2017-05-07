function(GenerateVersion VERSION_FILE)

  file(STRINGS ${VERSION_FILE} VERSION_STRING)
  string(REPLACE "." ";" VERSION_LIST ${VERSION_STRING})
  list(GET VERSION_LIST 0 VERSION_MAJOR)
  list(GET VERSION_LIST 1 VERSION_MINOR)
  list(GET VERSION_LIST 2 VERSION_PATCH)

  set(PROJECT_VERSION_MAJOR ${VERSION_MAJOR} PARENT_SCOPE)
  set(PROJECT_VERSION_MINOR ${VERSION_MINOR} PARENT_SCOPE)
  set(PROJECT_VERSION_PATCH ${VERSION_PATCH} PARENT_SCOPE)
endfunction(GenerateVersion)
