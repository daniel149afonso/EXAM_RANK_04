valgrind \
 --leak-check=full \
 --track-origins=yes \
 --show-leak-kinds=all \
 --track-fds=yes \
  ./shell echo salut | cat
