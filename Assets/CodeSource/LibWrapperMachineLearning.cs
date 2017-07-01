using System;
using System.Runtime.InteropServices;

public class LibWrapperMachineLearning
{

#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
    [DllImport("DllMachineLearningAPCT")] 
    public static extern System.IntPtr linear_create_model(int inputDimension, int outputDimension);

    [DllImport("DllMachineLearningAPCT")]
    public static extern void linear_remove_model(System.IntPtr model);

    [DllImport("DllMachineLearningAPCT")]
    public static extern System.IntPtr add_bias(System.IntPtr input, int inputSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern double linear_classify(System.IntPtr model, System.IntPtr input, int inputSize, System.IntPtr output, int ouputsSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern int linear_fit_classification_rosenblatt(System.IntPtr model, System.IntPtr inputs, int inputsSize, int inputSize, System.IntPtr outputs, int outputsSize, int iterationNumber, double step);

    [DllImport("DllMachineLearningAPCT")]
    public static extern System.IntPtr add_bias_regression(System.IntPtr inputs,System.IntPtr inputSize, System.IntPtr inputsSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern void transfoMatrixXd(IntPtr M, IntPtr input, int row, int col);

    [DllImport("DllMachineLearningAPCT")]
    public static extern void transfoArray(System.IntPtr M, System.IntPtr input, int row, int col);

    [DllImport("DllMachineLearningAPCT")]
    public static extern void linearPredict(System.IntPtr model, System.IntPtr input, int inputSize, System.IntPtr output, int outputSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern System.IntPtr pseudoInverse(System.IntPtr M, System.IntPtr N);

    [DllImport("DllMachineLearningAPCT")]
    public static extern int return42();

    [DllImport("DllMachineLearningAPCT")]
    public static extern int linear_fit_regression(System.IntPtr model, System.IntPtr inputs, int inputsSize, int inputSize, System.IntPtr outputs, int outputsSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern int linear_fit_classification_hebb(System.IntPtr model, System.IntPtr inputs, int inputsSize, int inputSize, int iterationNumber, double step);

    
    
    [DllImport("DllMachineLearningAPCT")]
    public static extern double linear_predict(System.IntPtr model, System.IntPtr input, int inputSize);

    [DllImport("DllMachineLearningAPCT")]
    public static extern int test();


    internal static int linear_fit_classification_rosenblatt(IntPtr model, IntPtr intPtr1, int v, int inputSize, IntPtr intPtr2, int iterationNumber, double step)
    {
        throw new NotImplementedException();
    }

    internal static int linear_fit_classification_hebb(IntPtr model, IntPtr intPtr1, int v, int inputSize, IntPtr intPtr2, int iterationNumber, double step)
    {
        throw new NotImplementedException();
    }

    //fucking erreur apared 
    /*internal static System.IntPtr linear_create_model(int v, int inputSize)
    {
        throw new NotImplementedException();
    }*/
#endif

    //lib pour par recoder l'inversion de matrice eigen

    //inputDimension -> pointeur sur un tableau de x paramétre plus 1 (x, y, neurones de biais)
    //inputSize -> taille du tableau nombre de caractere passée 
    //outpsSize -> taille du tableau de sortie 
    //iterationNumber -> le nombre d'iiteration a effectuér
    //step -> 
}