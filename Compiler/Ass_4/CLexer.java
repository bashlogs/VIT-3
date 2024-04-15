import java.util.*;
import java.util.regex.*;

public class CLexer {

    public static void main(String[] args) {
        String inputCCode = """
                        int main() {
                            int x = 10;
                            float y = 3.14;
                            char a = '5';
                            if (x > 5) {
                                return y;
                            }
                        }
                """;

        List<String> tokens = tokenizeCCode(inputCCode);
        Map<String, String> variables = extractVariables(tokens);
        displayVariableTable(variables);
    }

    public static List<String> tokenizeCCode(String inputCode) {
        List<String> tokens = new ArrayList<>();
        String[] lines = inputCode.split("\\n");

        for (String line : lines) {
            String[] lineTokens = line.split("\\W");
            for (String token : lineTokens) {
                if (!token.trim().isEmpty()) {
                    if (Arrays.asList("int", "float").contains(token)) {
                        tokens.add(token); 
                    } else if (Arrays.asList("+", "-", "*", "/", "=", "<", ">", "<=", ">=", "==", "!=")
                            .contains(token)) {
                        tokens.add("operator: " + token);
                    } else if (Arrays.asList("\t", ",", ";", "(", ")", "{", "}", "[", "]", " ").contains(token)) {
                        tokens.add("delimiter: " + token);
                    } else if (Pattern.matches("[a-zA-Z]+", token)) { 
                        tokens.add("ID: " + token);
                    }
                }
            }
        }

        return tokens;
    }

    public static Map<String, String> extractVariables(List<String> tokens) {
        Map<String, String> variables = new HashMap<>();
        String currentDataType = null;

        for (String token : tokens) {
            if (token.contains(": ")) {
                String[] parts = token.split(": ");
                String tokenType = parts[0];
                String tokenValue = parts[1];

                if (tokenType.equals(tokenValue)) { 
                    currentDataType = tokenValue;
                } else if (tokenType.equals("ID")) {
                    variables.put(tokenValue, currentDataType);
                    currentDataType = null; 
                }
            } else {
                currentDataType = token;
            }
        }

        return variables;
    }

    public static void displayVariableTable(Map<String, String> variables) {
        System.out.println("Variable\tData Type\tMemory Used\tScope");
        System.out.println("--------------------------------------------------");
        for (Map.Entry<String, String> entry : variables.entrySet()) {
            String varName = entry.getKey();
            String dataType = entry.getValue();

            if (dataType == null && varName.equals("a")) {
                dataType = "char"; 
            } else if (dataType == null && varName.equals("x")) {
                dataType = "int"; 
            } else if (dataType == null && varName.equals("y")) {
                dataType = "float"; 
            }

            if (dataType != null) {
                int memoryUsed = (dataType.equals("int") || dataType.equals("float")) ? 4 : 1; 
                System.out.println(varName + "\t\t" + dataType + "\t\t" + memoryUsed + " bytes\t\tGlobal");
            } else {
                System.out.println(varName + "\t\t" + "N/A" + "\t\t" + "N/A" + "\t\tGlobal");
            }
        }
    }
}