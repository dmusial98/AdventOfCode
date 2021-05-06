using System;
using System.Collections.Generic;
using System.Text;

namespace _12a
{
    class Program
    {
        static long epoch = 0, firstIndex = 0, lastIndex = 0;
        static int indexOfCurrentEpochString = 0, indexOfLastEpochString = 1;
        static String[] epochsStrings = new String[2] {"", "" };
        const long epochsNumber = 50000000000;

        static List<String> ReadFile()
        {
            System.IO.StreamReader file = null;
            String line;
            List<String> dataList = new List<String>();

            try
            {
                file = new System.IO.StreamReader("input.txt");

                if (!String.IsNullOrEmpty(line = file.ReadLine())) //read first line with initial state
                {
                    dataList.Add(line);
                }

                while (!String.IsNullOrEmpty(line = file.ReadLine()) && line.Length == 10) //reading rules
                    dataList.Add(line);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                if (file != null)
                    file.Close();
            }

            return dataList;
        }

        static void DoOneGeneration(List<string> rules)
        {
            StringBuilder currentEpochString = new StringBuilder(epochsStrings[indexOfCurrentEpochString]);
            StringBuilder lastEpochString = new StringBuilder(epochsStrings[indexOfLastEpochString]);
            int stringLength = currentEpochString.Length;
            
            for (int i = 0; i < stringLength; i++)
            {
                string pots;
                if (i == 0) //TODO: przerobić na switch'a
                    pots = ".." + currentEpochString.ToString().Substring(0, 3);
                else if (i == 1)
                    pots = "." + currentEpochString.ToString().Substring(0, 4);
                else if (i == stringLength - 2)
                    pots = currentEpochString.ToString().Substring(i, 4) + ".";
                else if (i == stringLength - 1)
                    pots = currentEpochString.ToString().Substring(i, 3) + "..";
                else
                    pots = currentEpochString.ToString().Substring(i, 5);


                int ruleIndex = 0;
                while (rules[ruleIndex].Substring(0, 5) != pots) //search index of rule
                    ruleIndex++;
                try
                { //skonczyc to szukanie i wstawianie
                    if (rules[ruleIndex][9] == '.')
                        lastEpochString[i] = '.';
                    else
                    {
                        if(i == 0 || i == 1 || i == stringLength - 2 || i == stringLength - 1)
                        {

                        }
                    }
                
                }
                catch(ArgumentOutOfRangeException e)
                {
                    Console.WriteLine("rule index out of range");
                }


            }

            indexOfCurrentEpochString = indexOfCurrentEpochString == 0 ? 1 : 0;
            indexOfLastEpochString = indexOfCurrentEpochString == 0 ? 0 : 1;
            epoch++;



        }

        static void Main(string[] args)
        {
            List<String> dataFromFile = ReadFile();
            epochsStrings[0] = dataFromFile[0]; //plants in 0 epoch
            dataFromFile.RemoveAt(0);
            lastIndex = epochsStrings[0].Length - 1;


            //int sumOFIndexes = 0;
            //foreach (Pot pot in PotsList[PotsList.Count - 1])
            //    if (pot.Content == '#')
            //        sumOFIndexes += pot.Index;

            //Console.WriteLine("\n\nNumber of plants: {0}", sumOFIndexes);

            Console.ReadKey();
        }
    }


}
