#include <QApplication>

#include "dialog.h"
#include "initializer.h"
#include "poolgame.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    PoolGame* game = Initializer().createPoolgame("../MacOS/config.json");

    //if the returned game is a nullptr the json file couldn't be found or was invalid
    if(!game) return a.exec();

    Dialog w(game);

    w.show();
    w.start();

    return a.exec();

}
