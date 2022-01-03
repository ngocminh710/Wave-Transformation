/* 
   This C++ program allows the user to open up the file input.txt,
read the music described there, print the music, transform the data 
into a .wav file, and generate output.wav.
*/ 

#include "song.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Note::Note(const string str)
{  
   switch(str[0]){
      case 'R':
         pitch = REST; break;
      case 'A':
         pitch = A;
         switch(str[1]){
            case 'b':
               pitch = Ab; break;
            case '#':
               pitch = Bb; break;}
         break;
      case 'B':
         pitch = B;
         switch(str[1]){
            case 'b':
               pitch = Bb; break;}
         break;
      case 'C':
         pitch = C;
         switch(str[1]){
            case '#':
               pitch = Db; break;}
         break;
      case 'D':
         pitch = D;
         switch(str[1]){
            case 'b':
               pitch = Db; break;
            case '#':
               pitch = Eb; break;}
         break;
      case 'E':
         pitch = E;
         switch(str[1]){
            case 'b':
               pitch = Eb; break;}
         break;
      case 'F':
         pitch = F;
         switch(str[1]){
            case '#':
               pitch = Gb; break;}
         break;
      case 'G':
         pitch = G;
         switch(str[1]){
            case 'b':
               pitch = Gb; break;
            case '#':
               pitch = Ab; break;}
         break;
      default:
         break;
   }
   
   char a;   
   if(str[1] != 'b' && str[1] != '#')
      a = str[1];
   else if(str[1] == 'b' || str[1] == '#')
      a = str[2];
   switch(a){
      case '0':
         octave = 0; break;
      case '1':
         octave = 1; break;
      case '2':
         octave = 2; break;
      case '3':
         octave = 3; break;
      case '4':
         octave = 4; break;
      case '5':
         octave = 5; break;
      case '6':
         octave = 6; break;
      case '7':
         octave = 7; break;
      default:
         break;
   }
          
   char b;      
   if(isalpha(str[2]))
      b = str[2];
   else 
      b = str[3];  
   switch(b){
      case 'q':
         duration = 1; break;
      case 'h':
         duration = 2; break;
      case 'w':
         duration = 4; break;
      case 'e':
         duration = 0.5; break;
      case 's':
         duration = 0.25; break;
      default:
         break;
   }
   
   if(str[str.size()-1] == '.')
      duration *= 1.5;
} 

Voice::Voice(const string& str, double vol, instrument_t instr)
{
   string note;
   
   istringstream ss;
   ss.str(str);
   while(ss >> note)
   {
      Note a(note);
      addNote(a);
   }
   
   setVolume(1000.0);
   setInstrument(TRUMPET);   
}

Song::Song(const string& file)
{
   string line, tempo, note;    
   vector<string> song;
      
   ifstream inFS;
   inFS.open(file);   
   if (!inFS.is_open()) 
      cout << "Could not open file." << endl;
 
   int i = 0; 
   while (!inFS.eof()) 
   {
      getline(inFS,line);
      if(inFS)
      {
         if(i == 0) 
         {
           tempo = line;
           song.push_back(tempo);
         }
         else if(i > 0)
         {
           note = line;
           song.push_back(note);  
         }
         i++;
      } 
   }

   unsigned t = stoi(song.at(0));
   setTempo(t);
   
   i = 1;
   while(i < song.size())
   {
      Voice b(song[i], 1000.0, TRUMPET);
      addVoice(b);
      i++;
   }
   inFS.close();
}

ostream& operator<<(ostream& out, const Note& n)
{
   switch(n.getPitch()){
      case REST: out << "R"; break;
      case A: out << "A"; break; 
      case B: out << "B"; break;
      case C: out << "C"; break;
      case D: out << "D"; break;
      case E: out << "E"; break;
      case F: out << "F"; break;
      case G: out << "G"; break;
      case Ab: out << "Ab"; break;
      case Bb: out << "Bb"; break;
      case Db: out << "Db"; break;
      case Eb: out << "Eb"; break;
      case Gb: out << "Gb"; break;}
         
   switch(n.getOctave()){
      case 0: out << 0; break;
      case 1: out << 1; break;
      case 2: out << 2; break;
      case 3: out << 3; break;
      case 4: out << 4; break;
      case 5: out << 5; break;
      case 6: out << 6; break;
      case 7: out << 7; break;}
      
   if(n.getDuration() == 1)
      out << 'q'; 
   else if(n.getDuration() == 2)
      out << 'h'; 
   else if(n.getDuration() == 4)
      out << 'w'; 
   else if(n.getDuration() == 0.5)
      out << 'e';
   else if(n.getDuration() == 0.25)
      out << 's'; 
   else if(n.getDuration() == 1.5)
      out << "q."; 
   else if(n.getDuration() == 3)
      out << "h."; 
   else if(n.getDuration() == 6)
      out << "w."; 
   else if(n.getDuration() == 0.75)
      out << "e."; 
   else if(n.getDuration() == 0.375)
      out << "s."; 

   return out;      
}

ostream& operator<<(ostream& out, const Voice& v)
{
   vector<Note> note = v.getNotes();
   
   for(int i = 0; i < note.size(); i++)
      out << note[i] << " ";
      
   return out;
}

ostream& operator<<(ostream& out, const Song& s)
{
   vector<Voice> voice = s.getVoices();
   
   out << s.getTempo() << endl;
 
   for(int i = 0; i < voice.size(); i++)
      out << voice[i] << " ";
      
   return out;
}