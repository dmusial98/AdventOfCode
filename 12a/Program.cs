using System;
using System.Collections.Generic;

namespace _12a
{
    public class Pot
    {
        public int Index { get; set; }
        public char Content { get; set; }
        public int Generation { get; }

        public Pot(int index, char content, int generation)
        {
            Index = index;
            Content = content;
            Generation = generation;
        }
    }

    public class Rule
    {
        public string RuleString { get; set; }
        public char FarLeft { get; set; }
        public char NearLeft { get; set; }
        public char Current { get; set; }
        public char NearRight { get; set; }
        public char FarRight { get; set; }
        public char Prediction { get; set; }

        public Rule(string ruleString)
        {
            RuleString = ruleString;

            FarLeft = RuleString[0];
            NearLeft = RuleString[1];
            Current = RuleString[2];
            NearRight = RuleString[3];
            FarRight = RuleString[4];
            Prediction = RuleString[9];
        }

    }


    class Program
    {
        const long GenerationNumberConst = 50000000000;
        static int GenerationNumber = 1;

        static List<List<Pot>> PotsList = new List<List<Pot>>();
        static List<Rule> RulesList = new List<Rule>();

        static void ReadFile()
        {
            System.IO.StreamReader file;
            string line;
            try
            {
                file = new System.IO.StreamReader("input.txt");

                if (!String.IsNullOrEmpty(line = file.ReadLine())) //read first line with initial state
                {
                    PotsList.Add(new List<Pot>());

                    int index = -5;
                    for (; index < 0; index++)
                        PotsList[0].Add(new Pot(index, '.', 0));
                    foreach (char pot in line)
                        PotsList[0].Add(new Pot(index++, pot, 0)); //making structure with initial state
                    for (int i = 0; i < 30; i++)
                        PotsList[0].Add(new Pot(index + i, '.', 0));
                }

                while (!String.IsNullOrEmpty(line = file.ReadLine()) && line.Length == 10) //reading rules
                    RulesList.Add(new Rule(line));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                //if(file != null)
                //    file.Close();
            }
        }

        static void Display()
        {
            int maxIndex = -2;

            for (int i = 0; i < PotsList.Count; i++)
                if (maxIndex < PotsList[i][PotsList[i].Count - 1].Index)
                    maxIndex = PotsList[i][PotsList[i].Count - 1].Index;

            for (int rowIndex = 0; rowIndex < 3; rowIndex++) //display columns with numbers of pots
            {
                Console.Write("        ");

                for (int columnIndex = 0; columnIndex <= maxIndex; columnIndex += 5)
                {
                    int hundredsDigit = columnIndex / 100;
                    int tensDigit = columnIndex % 100 / 10;
                    int unitsDigit = columnIndex % 10;

                    if (rowIndex == 0)
                    {
                        if (hundredsDigit == 0)
                            Console.Write(" ");
                        else
                            Console.Write(hundredsDigit);
                    }
                    else if (rowIndex == 1)
                    {
                        if (tensDigit != 0 || (hundredsDigit != 0 && tensDigit == 0))
                            Console.Write(tensDigit);
                        else
                            Console.Write(" ");
                    }
                    else if (rowIndex == 2)
                        Console.Write(unitsDigit);

                    Console.Write("    ");
                }
                Console.Write("\n");
            }

            bool generationDisplayed = false;
            foreach (List<Pot> potList in PotsList) //display pots with plants
            {
                foreach (Pot pot in potList)
                {
                    if (!generationDisplayed)
                    {
                        if (pot.Generation < 10)
                            Console.Write(" {0}:", pot.Generation);
                        else
                            Console.Write("{0}:", pot.Generation);

                        generationDisplayed = true;
                    }
                    Console.Write(pot.Content);
                }
                generationDisplayed = false;
                Console.Write("\n");
            }

        }

        static void DoOneGeneration()
        {
            PotsList.Add(new List<Pot>());
            PotsList[PotsList.Count - 1].Add(new Pot(-5, '.', GenerationNumber));
            PotsList[PotsList.Count - 1].Add(new Pot(-4, '.', GenerationNumber));

            for (int potIndex = 2; potIndex < PotsList[0].Count - 2; potIndex++)
            {
                char farLeft = PotsList[PotsList.Count - 2][potIndex - 2].Content;
                char nearLeft = PotsList[PotsList.Count - 2][potIndex - 1].Content;
                char current = PotsList[PotsList.Count - 2][potIndex].Content;
                char nearRight = PotsList[PotsList.Count - 2][potIndex + 1].Content;
                char farRight = PotsList[PotsList.Count - 2][potIndex + 2].Content;

                bool wasRule = false;

                foreach (Rule rule in RulesList)
                {
                    if (farLeft == rule.FarLeft && nearLeft == rule.NearLeft && current == rule.Current && nearRight == rule.NearRight && farRight == rule.FarRight)
                    {
                        PotsList[PotsList.Count - 1].Add(new Pot(potIndex - 5, rule.Prediction, GenerationNumber));
                        wasRule = true;
                        break;
                    }
                }

                if(!wasRule)
                    PotsList[PotsList.Count - 1].Add(new Pot(potIndex - 5, '.', GenerationNumber));
            }
            PotsList[PotsList.Count - 1].Add(new Pot(PotsList[PotsList.Count - 1][PotsList[PotsList.Count - 1].Count - 1].Index + 1, '.', GenerationNumber));
            PotsList[PotsList.Count - 1].Add(new Pot(PotsList[PotsList.Count - 1][PotsList[PotsList.Count - 1].Count - 1].Index + 2, '.', GenerationNumber));


            GenerationNumber++;
        }

        static void Main(string[] args)
        {
            ReadFile();

            for (int generationIndex = 0; generationIndex < GenerationNumberConst; generationIndex++)
                DoOneGeneration();

            Display();

            int sumOFIndexes = 0;
            foreach (Pot pot in PotsList[PotsList.Count - 1])
                if (pot.Content == '#')
                    sumOFIndexes += pot.Index;

            Console.WriteLine("\n\nNumber of plants: {0}", sumOFIndexes);

            Console.ReadKey();
        }
    }


}
