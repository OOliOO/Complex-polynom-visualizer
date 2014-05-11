#include "UI.hpp"

UI::UI(int w, int h):drawer(w,h){}

void UI::start(){
    drawer.setScale(200);
    auto command_listener=std::async(std::launch::async,getCommands);
    Polynom p;
    p.add(Term(std::complex<double>(0,1), 1));
    drawer.setPolynom(p);

    while(drawer.isRunning()){
        if(command_listener.wait_for(std::chrono::seconds(0))==std::future_status::ready){
            Command next_command=command_listener.get();
            if(next_command.type!=Command::CLOSE)
                command_listener=std::async(std::launch::async,getCommands);
            act(next_command);
        }
        drawer.update();
    }
}

void UI::act(Command cmd){
    if(cmd.type==Command::ERROR){
        std::cout<<"Invalid command (command help might help)"<<std::endl;
        return;
    }

    if(cmd.type==Command::HELP){
        help();
    }

    if(cmd.type==Command::CLOSE){
        drawer.close();
        return;
    }

    if(cmd.type==Command::MOVE_TO){
        drawer.setPointOfInterest(cmd.command_data[0].f,cmd.command_data[1].f);
        return;
    }

    if(cmd.type==Command::SET_ZOOM){
        drawer.setScale(cmd.command_data[0].f);
        return;
    }

    if(cmd.type==Command::SET_ARROW_DIST){
        drawer.setArrowDist(cmd.command_data[0].i);
        return;
    }

    if(cmd.type==Command::SET_LENGTH_MODE){
        switch(cmd.command_data[0].i){
            case 0:
                drawer.setLengthMode(Drawer::NORMAL);
                break;
            case 1:
                drawer.setLengthMode(Drawer::UNIVERSAL);
                break;
            case 2:
                drawer.setLengthMode(Drawer::LOGARITHMIC);
                break;
            case 3:
                drawer.setLengthMode(Drawer::SQRT);
                break;
        }
        return;
    }

    if(cmd.type==Command::SET_POLYNOM){
        drawer.setPolynom(cmd.poly);
        return;
    }
}

void UI::help(){
    std::cout<<"Commands:"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"move re im  -  moves the screen around the complex number defined by re and im"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"zoom scale  -  sets the zoom level, after this command width of scale pixels equals 1"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"lmode mode  -  changes the length mode, there are several of those:"<<std::endl;
    std::cout<<"univ  -  each line will have the same length"<<std::endl;
    std::cout<<"norm  -  linear normalization"<<std::endl;
    std::cout<<"sqrt  -  square root normalization"<<std::endl;
    std::cout<<"log   -  logarithmic normalization"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"dist line_dist -  sets the distance between the lines (by pixels)"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"exit  -  self-explanatory"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"setp  -  set polynom"<<std::endl;
    std::cout<<""<<std::endl;
}

Command getCommands(){
    std::string s;
    std::cin>>s;

    if(s=="move"){
        Command cmd;
        cmd.type=Command::MOVE_TO;
        std::string x,y;
        std::cin>>x>>y;
        if(isFloat(x)&&isFloat(y)){
            cmd.command_data[0].f=toFloat(x);
            cmd.command_data[1].f=toFloat(y);
        }else{
            cmd.type=Command::ERROR;
        }
        return cmd;
    }

    if(s=="zoom"){
        Command cmd;
        cmd.type=Command::SET_ZOOM;
        std::string scale;
        std::cin>>scale;
        if(isFloat(scale))
            cmd.command_data[0].f=toFloat(scale);
        else
            cmd.type=Command::ERROR;
        return cmd;
    }

    if(s=="lmode"){
        Command cmd;
        cmd.type=Command::SET_LENGTH_MODE;

        std::cin>>s;
        cmd.command_data[0].i=-1;

        if(s=="normal"||s=="norm")
            cmd.command_data[0].i=0;

        if(s=="universal"||s=="univ")
            cmd.command_data[0].i=1;

        if(s=="log")
            cmd.command_data[0].i=2;

        if(s=="sqrt")
            cmd.command_data[0].i=3;

        if(cmd.command_data[0].i==-1)
            cmd.type=Command::ERROR;

        return cmd;
    }

    if(s=="dist"){
        Command cmd;
        cmd.type=Command::SET_ARROW_DIST;
        std::string dist;
        std::cin>>dist;
        if(isFloat(dist))
            cmd.command_data[0].i=int(toFloat(dist));
        else
            cmd.type=Command::ERROR;
        return cmd;
    }

    if(s=="exit"){
        Command cmd;
        cmd.type=Command::CLOSE;
        return cmd;
    }

    if(s=="help"){
        Command cmd;
        cmd.type=Command::HELP;
        return cmd;
    }

    if(s=="setp"){
        Command cmd;
        cmd.type=Command::SET_POLYNOM;
        cmd.poly=getPolynom(); ///in streamtools.hpp
        return cmd;
    }

    Command cmd;
    cmd.type=Command::ERROR;
    return cmd;
}
