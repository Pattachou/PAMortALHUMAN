using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class WrapperLibScriptUser : MonoBehaviour
{

    public static System.IntPtr model;

    public int launch = 0; //variable pour savoir si un algo tourne ou pas 0 ok n'est pas en cours
    public int iterationNumber = 100;
    public double step = 0.75;
    public Transform[] learnObject;//tableau avec les données pour l'apprentissage
    public Transform[] testObject;//tableau avec les données pour les test 

    void Start()
    {
        
    }


    //méthode affichant les boutons et gérant les evenements 
    public void OnGUI()
    {
        if (GUILayout.Button("Création du modéle"))
            //création du modéle associé a un pointeur
        {
            if (launch == 0)
            {
                //Debug.Log("onGui");
                createModel();
                
            }
        }
        if (GUILayout.Button("Suppression du modéle"))
            //orientation du pointeur sur zéro
        {
            if (launch == 0)
            {
                removeModel();
            }
        }
        if (GUILayout.Button("Classification linéaire "))
        {
            if (launch == 0)
            {
                linClass();
            }
        }
        if (GUILayout.Button("Classificationde linéaire de Rosenblatt"))
        {
            if (launch == 0)
            {
                classifRosenblatt();
            }
        }
        if (GUILayout.Button("Classification linéaire de Hebb"))
        {
            if (launch == 0)
            {

            }
        }
        if (GUILayout.Button("Prédiction linéaire"))
        {
            if (launch == 0)
            {

            }
        }
        if(GUILayout.Button("Régression linéaire"))
        {
            if(launch == 0)
            {

            }
        }
    }

    public void createModel()
    {
        launch = 1;
        if (model == System.IntPtr.Zero)
        {
            model = LibWrapperMachineLearning.linear_create_model(2,1); //le nombre de coordonnée du point 
            Debug.Log("Nouveau modéle : " + model);
        } else
        {
            Debug.Log("Le modéle est déjà existant --> " + model);
        }
        /*Debug.Log("create model " + learnObject);
        foreach(var data in learnObject)
        {
            Debug.Log(data.transform.name + "learnObject");
        }*/
        launch = 0;
        //permert de recupere le dossier sphere d'apprentissage et tout ces sous objets
        //learnObject = GameObject.Find("LearnSphere").transform[];

        /*if (learnObject)
        {
            model = LibWrapperMachineLearning.linear_create_model(2);//x + z
            Debug.Log("Model create ! " + model);
            Debug.Log(learnObject.transform.childCount);
            
            // count le nombre d'objet contenue dans Sphere Apprentissage
            /*int nbSphereLearn = goLearn.transform.childCount;
            for (int i = 0; i < nbSphereLearn; i++)
            {
                learnObject[i] = goLearn.transform.GetChild(i);
                zPos[i] = goLearn.transform.GetChild(i).position.z;
                Debug.Log(goLearn.transform.GetChild(i).position.x + "---------" + goLearn.transform.GetChild(i).position.z + "------" + i);


            }
            //learnObject[i] = transform.GetChild(i).position.x;
        }
        else
        {
            Debug.Log("Model NOK");
        }
        launch = 0; */
    }

    public void removeModel()
    {
        launch = 1;
        //Debug.Log("Remove model");
        if (model != System.IntPtr.Zero)
        {
            LibWrapperMachineLearning.linear_remove_model(model);
            model = System.IntPtr.Zero;
            Debug.Log("Model supprimé !");
        }
        else
        {
            Debug.Log("removeModel : Il n'y a pas de modéle");
        }
        launch = 0;

    }

    public void linClass()
    {
        launch = 1;
        if(model != System.IntPtr.Zero)
        {
            double[] input = new double[2];
            double[] output = new double[1];
            foreach (var unityObject in testObject)
            {
                input[0] = unityObject.position.x;
                input[1] = unityObject.position.z;
                var inPtr = GCHandle.Alloc(input, GCHandleType.Pinned);
                var ouPtr = GCHandle.Alloc(output, GCHandleType.Pinned);
                if ((float)LibWrapperMachineLearning.linear_classify(model, inPtr.AddrOfPinnedObject(), 2,ouPtr.AddrOfPinnedObject(),1) == 1)
                {
                    unityObject.GetComponent<Renderer>().material.color = UnityEngine.Color.red;
                } else
                {
                    unityObject.GetComponent<Renderer>().material.color = UnityEngine.Color.green;
                }
                if(inPtr.IsAllocated)
                {
                    inPtr.Free();
                }
                
            }
        }
        else
        {
            Debug.Log("linClass : Il n'y a pas de modéle");
        }
        launch = 0;
    }

    public void classifRosenblatt()
    {
        launch = 1;
        if (model != System.IntPtr.Zero)
        {
            double[] input = new double[2 * learnObject.Length];
            double[] output = new double[learnObject.Length];
            getInOutput(learnObject, input, output);

            var inPtr = GCHandle.Alloc(input, GCHandleType.Pinned);
            var ouPtr = GCHandle.Alloc(output, GCHandleType.Pinned);
            Debug.Log(model);
            int retur = LibWrapperMachineLearning.linear_fit_classification_rosenblatt(model, inPtr.AddrOfPinnedObject(), 2 * learnObject.Length, 2, ouPtr.AddrOfPinnedObject(),1,iterationNumber,step); ;
            if(retur == -1)
            {
                Debug.Log("classifRosenblattRetur : Il n'y a pas de modéle");
            }
            else if(retur == 0)
            {
                Debug.Log("L'algorithme a été arrêter par le nombre d'itteration");
            }
            else
            {
                Debug.Log("L'algorithme à fini son travail");
            }
            if(inPtr.IsAllocated)
            {
                inPtr.Free();
            }
            if (ouPtr.IsAllocated)
            {
                ouPtr.Free();
            }

        } else
        {
            Debug.Log("classifRosenblatt : Il n'y a pas de modéle");
        }
        launch = 0;
    }


    public void getInOutput(Transform[] objectUnity, double[] input, double[] output)
    {
        int i = 0;
        int j = 0;
        foreach ( var data in objectUnity)
        {
            input[i] = data.position.x;
            input[i + 1] = data.position.z;
            i += 2;
            output[j] = data.position.y;
            j++;
        }
    }



}