package Java;
import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;


public class DataDisplay {

    public String HTMLfromat(String s) 
    {
        StringBuilder builder = new StringBuilder();
        boolean previousWasASpace = false;
        for( char c : s.toCharArray() ) {
            if( c == ' ' ) {
                if( previousWasASpace ) {
                    builder.append("&nbsp;");
                    previousWasASpace = false;
                    continue;
                }
                previousWasASpace = true;
            } else {
                previousWasASpace = false;
            }
            switch(c) {
                case '<': builder.append("&lt;"); break;
                case '>': builder.append("&gt;"); break;
                case '&': builder.append("&amp;"); break;
                case '"': builder.append("&quot;"); break;
                case '\n': builder.append("<br>"); break;
                // We need Tab support here, because we print StackTraces as HTML
                case '\t': builder.append("&nbsp; &nbsp; &nbsp;"); break;  
                default:
                    if( c < 128 ) {
                        builder.append(c);
                    } else {
                        builder.append("&#").append((int)c).append(";");
                    }    
            }
        }
        return builder.toString();
    }
    private static String readFile(String filePath)
    {
        // Declaring object of StringBuilder class
        StringBuilder builder = new StringBuilder();
        // try block to check for exceptions where
        // object of BufferedReader class us created
        // to read filepath
        try (BufferedReader buffer = new BufferedReader(
                 new FileReader(filePath))) {
 
            String str;
            // Condition check via buffer.readLine() method
            // holding true upto that the while loop runs
            while ((str = buffer.readLine()) != null) {
 
                builder.append(str).append("\n");
            }
        }
        // Catch block to handle the exceptions
        catch (IOException e) {
            // Print the line number here exception occurred
            // using printStackTrace() method
            e.printStackTrace();
        }
        // Returning a string
        return builder.toString();
    }

    public String data(String selection){
        if(selection == "Hash Map"){
            String filePath = "C++ Libraries/Hash Map/UnorderedMap.h";
            String rawData = readFile(filePath);
            return HTMLfromat(rawData);
        }
        else if(selection == "Link_list"){

        }
        else if(selection == "Vector"){
            String filePath = "C++ Libraries/Vector.h";
            String rawData = readFile(filePath);
            return HTMLfromat(rawData);
        }

        return "No valid selection Made";
    }
}
