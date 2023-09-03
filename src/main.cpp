#include "MidiFile.h"
#include "Options.h"
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;
using namespace smf;

// map 0 - 1023 to 0 - 255
// map(val, 0, 1023, 0, 255);
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void statistics(const std::vector<double> &input)
{
   // Compute statistics of the generated samples
   double mean = std::accumulate(input.begin(), input.end(), 0.0) / input.size();
   double variance = 0.0;
   for (double value : input)
   {
      variance += (value - mean) * (value - mean);
   }
   variance /= input.size();
   double standardDeviation = std::sqrt(variance);

   // Print the statistics
   std::cout << "samples statistics:" << std::endl;
   std::cout << "Mean: " << mean << std::endl;
   std::cout << "Variance: " << variance << std::endl;
   std::cout << "Standard Deviation: " << standardDeviation << std::endl;
}

int main(int argc, char **argv)
{
   // Options options;
   // options.define("n|note-count=i:10", "How many notes to randomly play");
   // options.define("o|output-file=s",   "Output filename (stdout if none)");
   // options.define("i|instrument=i:0",  "General MIDI instrument number");
   // options.define("x|hex=b",           "Hex byte-code output");
   // options.process(argc, argv);

   // {
   //    random_device rd;
   //    mt19937 mt(rd());
   //    uniform_int_distribution<int> starttime(0, 100);
   //    uniform_int_distribution<int> duration(1, 8);
   //    uniform_int_distribution<int> pitch(36, 84);
   //    uniform_int_distribution<int> velocity(40, 100);

   //    MidiFile midifile;
   //    int track   = 0;
   //    int channel = 0;
   //    int instrument   = options.getInteger("instrument");
   //    midifile.addTimbre(track, 0, channel, instrument);

   //    int tpq     = midifile.getTPQ();
   //    int count   = options.getInteger("note-count");
   //    for (int i=0; i<count; i++) {
   //       int starttick = int(starttime(mt) / 4.0 * tpq);
   //       int key       = pitch(mt);
   //       int endtick   = starttick + int(duration(mt) / 4.0 * tpq);
   //       midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
   //       midifile.addNoteOff(track, endtick,   channel, key);
   //    }

   //    midifile.sortTracks();  // Need to sort tracks since added events are
   //                            // appended to track in random tick order.
   //    string filename = options.getString("output-file");
   //    if (filename.empty()) {
   //       if (options.getBoolean("hex")) midifile.writeHex(cout);
   //       else cout << midifile;
   //    } else
   //       midifile.write(filename);
   // }

   std::vector<double> samples;

   {
      // edit the output file, set all the notes to have velocity 127
      string filename = "..\\open high-hats.mid"; // options.getString("output-file");
      if (filename.empty())
      {
         return -1;
      }

      MidiFile midifile;
      midifile.read(filename);

      bool off = true;

      for (int i = 0; i < midifile[1].getSize(); i++)
      {
         // 0–127
         const auto v = midifile[1][i].getVelocity();
         if (v > 0 && off)
         {
            off = false;
            // cout << midifile[1][i].getKeyNumber() << ":" << v << endl;
            samples.push_back(static_cast<double>(v));
            off = true;
         }
      }
      // midifile.write(filename + ".v2.mid");
   }

   {
      for (int i = 0; i < samples.size(); i++)
      {
         // 0–127
         cout << samples.at(i) << endl;
      }

      statistics(samples);
   }

   {
      const int numSamples = 100;
      std::vector<double> generatedSamples(numSamples);
      for (int i = 0; i < numSamples; ++i)
      {
         generatedSamples.at(i) = generateRandomNumber(samples);
      }

      for (int i = 0; i < generatedSamples.size(); i++)
      {
         // 0–127
         cout << generatedSamples.at(i) << endl;
      }

      statistics(generatedSamples);
   }

   return 0;
}