#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
using namespace std;

bool useStarAndBlank = true;

/*******************************************************************
 * A class that represents a Wire with a current and a new boolean
 * value.  The new value is set by the operation of a Cell, and it
 * will become the current value after being updated, which typically
 * happens right before showing (outputting) the value.
 *******************************************************************/

class Wire

{
    
private:
    
    bool mValue;
    
    bool mNewValue;
    
    
    
public:
    
    /****************************************************************
     
     * Constructs a new wire instance with a default value (false).
     
     ****************************************************************/
    
    Wire()
    
    {
        
        setValue(false);
        
        setNewValue(false);
        
    }
    
    
    
    /****************************************************************
     
     * Constructs a new wire instance with a given value.
     
     ****************************************************************/
    
    Wire(bool pValue)
    
    {
        
        setValue(pValue);
        
        setNewValue(false);
        
    }
    
    
    
    /******************************
     
     * Gets this wire's value.
     
     *******************************/
    
    bool getValue() const { return mValue; }
    
    
    
    /******************************
     
     * Gets this wire's new value.
     
     *******************************/
    
    bool getNewValue() const { return mNewValue; }
    
    
    
    /******************************
     
     * Sets this wire's value.
     
     *******************************/
    
    void setValue(bool pValue) { mValue = pValue; }
    
    
    
    /******************************
     
     * Sets this wire's new value.
     
     *******************************/
    
    void setNewValue(bool pNewValue) { mNewValue = pNewValue; }
    
    
    
    /******************************
     
     * Sets this wire's value to its new value.
     
     *******************************/
    
    void setValueToNew() { mValue = mNewValue; }
    
    
    
    /****************************************************
     
     * Gets the character representing this wire's value.
     
     ****************************************************/
    
    char getCharacterRepresentingValue() const
    
    {
        
        return
        
        ((useStarAndBlank) ?
         
         (getValue() ? '*' : ' ') :
         
         (getValue() ? '1' : '0'));
        
    }
    
};



/****************************************************************
 
 * Outputs a Wire.
 
 ****************************************************************/

ostream& operator<<(ostream& os, const Wire& w)

{
    
    os << w.getCharacterRepresentingValue();
    
    return os;
    
}



/****************************************************************
 
 * A base class representing a Boolean function of degree 3.
 
 ****************************************************************/

class BooleanFunction3

{
    
protected:
    
    
    
    
    
public:
    
    bool mValues[8];
    
    BooleanFunction3()
    
    {
        
        for (int i = 0; i < 8; i++)
            
        {
            
            mValues[i] = false;
            
        }
        
    }
    
    
    
    bool evaluate(bool p1, bool p2, bool p3)
    
    {
        
        int i = 0;
        
        if (p3)
            
        {
            
            i |= 1;
            
        }
        
        if (p2)
            
        {
            
            i |= 2;
            
        }
        
        if (p1)
            
        {
            
            i |= 4;
            
        }
        
        return mValues[i];
        
    }
    
    
    
    void populate(int values)
    
    {
        
        int i = 0;
        
        while (values > 0)
            
        {
            
            mValues[i++] = ((values & 1) == 1);
            
            values /= 2;
            
        }
        
    }
    
};



/****************************************************************
 
 * A Cell implementing a boolean function of degree 3.
 
 ****************************************************************/

class Cell

{
    
protected:
    
    BooleanFunction3* mBooleanFunction3;
    
    
    
public:
    
    /****************************************************************
     
     * Constructs a new Cell instance with three wires and
     
     * a pointer to a Boolean Function of degree 3.
     
     *
     
     * This merely has the side effect of computing the boolean
     
     * function on the three wire inputs, storing the result in the
     
     * middle (output) wire.
     
     ****************************************************************/
    
    Cell(Wire& x, Wire& y, Wire& z, BooleanFunction3* pBooleanFunction3)
    
    {
        
        setBooleanFunction3(pBooleanFunction3);
        
        y.setNewValue(getBooleanFunction3()->evaluate(
                                                      
                                                      x.getValue(), y.getValue(), z.getValue()));
        
    }
    
    
    
    /****************************************************************
     
     * Gets the pointer to the Boolean Function of degree 3.
     
     ****************************************************************/
    
    BooleanFunction3* getBooleanFunction3()
    
    {
        
        return mBooleanFunction3;
        
    }
    
    
    
    /****************************************************************
     
     * Sets the pointer to the Boolean Function of degree 3.
     
     ****************************************************************/
    
    void setBooleanFunction3(BooleanFunction3* pBooleanFunction3)
    
    {
        
        mBooleanFunction3 = pBooleanFunction3;
        
    }
    
};



/****************************************************************
 
 * Main is for you to explore...
 
 ****************************************************************/
int main(int argc, char* argv[])
{
    // if less than one argument, show usage
    if (argc <= 1)
    {
        cout << "Usage: " << argv[0] << " [binary filenames][numCells][numSteps][showStars]" << endl;
        return 0;
    }
    
    int numCells = 100;
    int numSteps = numCells;
    bool useBinFileNames = false;
    
    if (argc > 1)
    {
        useBinFileNames = atoi(argv[1]) == 0 ? false : true;
        
        if (argc > 2)
            numCells = atoi(argv[2]);
        if (argc > 3)
            numSteps = atoi(argv[3]);
        if (argc > 4)
            useStarAndBlank = atoi(argv[4]) == 0 ? false : true ;
    }
    
    // TODO: get program input another (better?) way.
    
    //loop through every combination
    for (int funcNum = 0; funcNum < 255; funcNum++)
    {
        ofstream fout;
        fout.open((useBinFileNames ? bitset<8>(funcNum).to_string() : to_string(funcNum)) + ".tbl");
        if (fout.fail())
        {
            cerr << "Error writting file " << funcNum << ".tbl";
            break;
        }
        
        // TODO: create numCells Wires.
        Wire * wires = new Wire[numCells];
        
        // TODO: set to true the new value of the middle-most Wire
        //       (the middle of the whole array, *NOT* the middle wire of each cell).
        
        wires[numCells/2].setValue(true);
        
        // TODO: update values to new values and show (output) all Wires.
        for (int i = 0; i < numCells; i++)
        {
            //wires[i].setValueToNew();
            fout << wires[i];
        }
        fout << endl;
        
        // TODO: create a BooleanFunction3 given the booleanFunctionNumber.
        BooleanFunction3* boolFunc = new BooleanFunction3();
        boolFunc->populate(funcNum);
        
        // TODO: iterate A and B for numSteps steps.
        for (int currentStep = 0; currentStep < numSteps - 1; currentStep++)
        {
            // TODO: A) create the network of Cells implementing the BooleanFunction3
            //          and connect them to the numCells Wires, as per the write-up.
            for (int i = 1; i < numCells - 1; i++)
                Cell (wires[i + 1], wires[i], wires[i - 1], boolFunc);
            
            // TODO: B) update values to new values and show (output) all wires.
            for (int i = 0; i < numCells; i++)
            {
                wires[i].setValueToNew();
                fout << wires[i];
            }
            fout << endl;
        }
        
        //delete dynanically allocated vars
        delete[] wires;
        delete boolFunc;
        
        //close file out stream
        fout.close();
    }
    
    return 0;
}