target_sources(taller_common
    PRIVATE
    # .cpp files
    liberror.cpp
    protocol.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp

    PUBLIC
    # .h files
    liberror.h
    protocol.h
    resolver.h
    resolvererror.h
    socket.h
    connectioneExceptions.h
    )