       #include <sys/socket.h>

int main ()
{
ssize_t i = 0;

i = send(2222, "hello", 6, 0);

return (i);

}
