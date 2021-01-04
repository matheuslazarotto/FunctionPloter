/** Function parser and ploter 
 * 
 * The present code receives a string input 
 * and parse it to a real function to evaluate 
 * its values and return it to a '.dat' file 
 * from where it can be ploted. 
 *  
 * Credits:
 * This code is just an interface for the 
 * remarkable Exprtk function parser code, 
 * made by Arash Partow. The code, manual 
 * and files can be found at:
 * http://www.partow.net/programming/exprtk/
 * In readme/ folder the original readme.txt 
 * can be found with instructions on the 
 * method.
 * 
 * Install and Usage: type 'make' to compile
 * (it may take a few seconds and ~1.5GB of 
 *  RAM) and then type './func_ploter' to run 
 * this code.
 * 
 * Made by: M. Lazarotto (30/09/2020)
 **/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <fstream>
#include <cstring>
#include <string>
#include "../include/exprtk.hpp"

using namespace std;

void remove_chars(string& text, const string& chars);
bool in_text(const string& text, const string& pattern);
bool check_setup(const string& text, const string& setup_id);
vector<string> split_string(const string& text, const string& delim = " ");

int main(int argc, char **argv)
{
	/** Read data **/
	const char *filename = argv[1];
	ifstream DataFile(filename);

	int nPoints;
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	string line;
	string sVariable;
	vector<string> vExpressions;
	vector<pair<string, double>> vConstants;
	
	while (getline(DataFile, line))
	{
		if (check_setup(line, "f"))     	 { vExpressions.push_back(split_string(line, "=")[1]); }
		else if (check_setup(line, "var"))   { sVariable = split_string(line, "=")[1];  	       }
		else if (check_setup(line, "x_min")) { x_min = stof(split_string(line, "=")[1]); 	       }
		else if (check_setup(line, "y_min")) { y_min = stof(split_string(line, "=")[1]); 	       }
		else if (check_setup(line, "x_max")) { x_max = stof(split_string(line, "=")[1]); 	       }
		else if (check_setup(line, "y_max")) { y_max = stof(split_string(line, "=")[1]); 	       }
		else if (check_setup(line, "Npts"))  { nPoints = stoi(split_string(line, "=")[1]);         }
		else if (check_setup(line, "cte"))
		{
			string constant_name = split_string(line, "=")[1];
			double constant_value = stof(split_string(line, "=")[2]);
			vConstants.push_back(make_pair(constant_name, constant_value));
		}
	}

	// Remove undesirable chars
	remove_chars(sVariable, " ");
	for (auto &c : vConstants) { remove_chars(c.first, " "); }

	/** Loop over functions **/
	int id = 0;
	for (auto function : vExpressions)
	{
		auto start = chrono::steady_clock::now();

		double x;
		exprtk::parser<double> parser;
		exprtk::expression<double> expression;
		exprtk::symbol_table<double> symbol_table;

		// Set and parse function
		symbol_table.add_variable(sVariable, x);
		for (auto c : vConstants) { symbol_table.add_constant(c.first, c.second); }
		symbol_table.add_constants();
		
		expression.register_symbol_table(symbol_table);
		parser.compile(function, expression);

		// Run calculation
		char fname[100];
    	sprintf(fname, "output_%d.dat", id);
    	FILE *fout = fopen(fname, "w");
		fprintf(fout, "# function => %s\n", function.c_str());
		fprintf(fout, "# x_min = %f\n", x_min);
		fprintf(fout, "# x_max = %f\n", x_max);
		fprintf(fout, "# y_min = %f\n", y_min);
		fprintf(fout, "# y_max = %f\n", y_max);
		fprintf(fout, "# [x]   [f(x)]\n");
	
		const double dx = fabs(x_max - x_min) / (double) nPoints;
		for (x = x_min; x <= x_max; x += dx)
		{
			double y = expression.value();
			fprintf(fout, "%f   %f\n", x, y);
		}

		fclose(fout);
		id += 1;

    	auto end = chrono::steady_clock::now();
    	cout << "Elapsed time (f(x) = " << function << "): " 
			 << chrono::duration_cast<chrono::seconds>(end - start).count() << "sec "
			 << chrono::duration_cast<chrono::milliseconds>(end - start).count() % 1000 << "millisec "
			 << chrono::duration_cast<chrono::microseconds>(end - start).count() % 1000 << "microsec\n" << endl;
	}

	return 0;
}

void remove_chars(string& text, const string& chars)
{
	// Will remove 
	for (unsigned int i = 0; i < chars.length(); i += 1)
	{
		text.erase(std::remove(text.begin(), text.end(), chars[i]), text.end());
	}
}

bool in_text(const string& text, const string& pattern)
{
	for (int i = 0; i <= (int)(text.length() - pattern.length()); i += 1)
	{
		if (pattern.length() <= (text.length() - i))
		{
			if (text.compare(i, pattern.length(), pattern) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool check_setup(const string& text, const string& setup_id)
{
	if (in_text(text, setup_id + "=")  || in_text(text, setup_id + "= ") ||
		in_text(text, setup_id + " =") || in_text(text, setup_id + " = "))
	{
		return true;
	}

	return false;
}

std::vector<string> split_string(const string& text, const string& delim)
{
	std::vector<string> splitted_text;

    std::size_t current = 0;
	std::size_t previous = 0;
    
	current = text.find(delim);

	// Handle empty delim
	if (delim.length() == 0)
	{
		splitted_text.push_back(text);
		return splitted_text;
	}

	while (current != std::string::npos) 
	{
		if (text.substr(previous, current - previous).length() > 0)
		{
        	splitted_text.push_back(text.substr(previous, current - previous));
		}
        previous = current + delim.length();
        current = text.find(delim, previous);
    }
	
	if (text.substr(previous, current - previous).length() > 0)
	{
		splitted_text.push_back(text.substr(previous, current - previous));
	}
	
	return splitted_text;
}