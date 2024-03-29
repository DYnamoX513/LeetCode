cmake_minimum_required(VERSION 3.17)
project(LeetCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(utils)

aux_source_directory(utils UtilFiles)

add_executable(0001 1-200/1_20.cpp ${UtilFiles})

add_executable(others ungrouped.cpp ${UtilFiles})

list(APPEND l1 21 41 61 81)
list(APPEND l20 40 60 80 100)
foreach(start end IN ZIP_LISTS l1 l20)
    if (EXISTS ../1-200/${start}_${end}.cpp)
        add_executable(00${start} 1-200/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l101 101 121 141 161 181)
list(APPEND l120 120 140 160 180 200)
foreach(start end IN ZIP_LISTS l101 l120)
    if (EXISTS ../1-200/${start}_${end}.cpp)
        add_executable(0${start} 1-200/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l201 201 221 241 261 281 301 321 341 361 381)
list(APPEND l220 220 240 260 280 300 320 340 360 380 400)
foreach(start end IN ZIP_LISTS l201 l220)
    if (EXISTS ../201-400/${start}_${end}.cpp)
        add_executable(0${start} 201-400/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l401 401 421 441 461 481 501 521 541 561 581)
list(APPEND l420 420 440 460 480 500 520 540 560 580 600)
foreach(start end IN ZIP_LISTS l401 l420)
    if (EXISTS ../401-600/${start}_${end}.cpp)
        add_executable(0${start} 401-600/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l601 601 621 641 661 681 701 721 741 761 781)
list(APPEND l620 620 640 660 680 700 720 740 760 780 800)
foreach(start end IN ZIP_LISTS l601 l620)
    if (EXISTS ../601-800/${start}_${end}.cpp)
        add_executable(0${start} 601-800/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l801 801 821 841 861 881 901 921 941 961 981)
list(APPEND l820 820 840 860 880 900 920 940 960 980 1000)
foreach(start end IN ZIP_LISTS l801 l820)
    if (EXISTS ../801-1000/${start}_${end}.cpp)
        add_executable(0${start} 801-1000/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l1001 1001 1021 1041 1061 1081 1101 1121 1141 1161 1181)
list(APPEND l1020 1020 1040 1060 1080 1100 1120 1140 1160 1180 1200)
foreach(start end IN ZIP_LISTS l1001 l1020)
    if (EXISTS ../1001-1200/${start}_${end}.cpp)
        add_executable(${start} 1001-1200/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l1201 1201 1221 1241 1261 1281 1301 1321 1341 1361 1381)
list(APPEND l1220 1220 1240 1260 1280 1300 1320 1340 1360 1380 1400)
foreach(start end IN ZIP_LISTS l1201 l1220)
    if (EXISTS ../1201-1400/${start}_${end}.cpp)
        add_executable(${start} 1201-1400/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l1401 1401 1421 1441 1461 1481 1501 1521 1541 1561 1581)
list(APPEND l1420 1420 1440 1460 1480 1500 1520 1540 1560 1580 1600)
foreach(start end IN ZIP_LISTS l1401 l1420)
    if (EXISTS ../1401-1600/${start}_${end}.cpp)
        add_executable(${start} 1401-1600/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()

list(APPEND l1601 1601 1621 1641 1661 1681 1701 1721 1741 1761 1781)
list(APPEND l1620 1620 1640 1660 1680 1700 1720 1740 1760 1780 1800)
foreach(start end IN ZIP_LISTS l1601 l1620)
    if (EXISTS ../1601-1800/${start}_${end}.cpp)
        add_executable(${start} 1601-1800/${start}_${end}.cpp ${UtilFiles})
    endif ()
endforeach()