#include <iostream>
using namespace std;

class Message {
  int myId;
  public:
    operator int() { return myId; }
    Message(int id) : myId(id) {}
/*
  equalTo - the Message Obect determines its equality with another message object. This may well be an == operator
*/
    bool equalTo(int id) {
      return id % myId == 0;
    }
};

class HandlerBase {

  Message myMessage;
  protected:
    HandlerBase *m_successor;
  public:
    HandlerBase(HandlerBase *s, Message *m) : m_successor(s), myMessage(*m) {}
    void HandleMessage(Message *m) {
        if(myMessage.equalTo(*m)) { // test equality with own message and handle it
            cout << "Message " << *m << " got handled by " << myMessage << "\n";
        } else if(m_successor) { // else hand over to next handler in line
            cout << "Message " << *m << " got handed to successor" << "\n";
            m_successor->HandleMessage(m);
        } else { // or if this was the last handler, give up
            cout << "Message " << *m << " had no handler" << "\n";
        }
    }
};

int main() {
  Message m1(3), m2(5), m3(7), m4(4);
  HandlerBase h1(0, &m1), h2(&h1,&m2), h3(&h2,&m3), h4(&h3,&m4); // create handler chain h4 <> h3 <> h2 <> h1
  int m;
  while(cin >> m) {
    Message newMsg(m);
    h4.HandleMessage(&newMsg);
  }
  return 0;
}



