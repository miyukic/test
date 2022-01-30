// See https://aka.ms/new-console-template for more information
using System.Threading.Tasks;
using System.Threading;

Task.Run( () => {
});

Console.WriteLine("Hello, World!");
string? input = Console.ReadLine();
Console.WriteLine(input);

int GetMessage(Message msg) {
    if (msg.id == 0) {
        Thread.Sleep();
    }
    return -1;
}

void Dispatch(Message msg) {

}

int check = 0;
while (check = GetMessage(msg)) {
    if (check == -1) break;
    Dispatch(in msg);
}

class Message {
    public int id;
}
