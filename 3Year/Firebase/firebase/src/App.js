import './App.css';
import { Auth } from './components/auth';
import { db } from './config/firebase';
import { useEffect, useState } from 'react';
import { getDocs, collection } from 'firebase/firestore';

function App() {
  const [movieList, setMovieList] = useState([]); 
  const moviesCollectionsRef = collection(db, 'movies');  
  useEffect(() => {
    const getMovieList = async () => {
        try{
          const data = await getDocs(moviesCollectionsRef); 
          console.log(data);
        }
        catch(error){
          console.log(error);
        }
    };

    getMovieList(); 
  }, []);
  
  return (
    <div className="App">
      <Auth />
    </div>

  );
}

export default App;
