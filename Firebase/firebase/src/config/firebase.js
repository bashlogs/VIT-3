// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth, GoogleAuthProvider } from 'firebase/auth';
import { getFirestore } from 'firebase/firestore';

// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyDQxpPvE2y5O5T9LwfsTbtZgxjRizCLuGg",
  authDomain: "firebasic-2cfd8.firebaseapp.com",
  projectId: "firebasic-2cfd8",
  storageBucket: "firebasic-2cfd8.appspot.com",
  messagingSenderId: "728701541090",
  appId: "1:728701541090:web:3523ba41726f6b3dcc9cbb",
  measurementId: "G-VD9816KBC0"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
export const auth = getAuth(app)
export const googleProvider = new GoogleAuthProvider();
export const db = getFirestore(app);