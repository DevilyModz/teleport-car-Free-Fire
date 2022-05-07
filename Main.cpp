/* Create by DevilyModz */
/* Please add Credit for name me */

static void *Get_LocalPlayer(void* Match) 
{
    void *(*_Get_LocalPlayer)(void *match) = (void *(*)(void *))getRealOffset(0x20218E8);
    return _Get_LocalPlayer(Match);
}

static void *get_Match() 
{
    void *(*_get_Match) (void *nuls) = (void *(*)(void *))getRealOffset(0x10D21DC);
    return _get_Match(NULL);
}

static void *Tele_LocalVehicle(void* local) 
{
    void *(*_Tele_LocalVehicle)(void * player) = (void *(*)(void *))getRealOffset(0xBF0AA4); //[1.80]
    return _Tele_LocalVehicle(local);
}

void (*orig_LateUpdateVehicle)(void* player);
void hook_LateUpdateVehicle(void* player) 
{
    if (orig_LateUpdateVehicle) 
    {        
         void* Match = get_Match();
         if (Match) 
         {
              void* LocalPlayer = Get_LocalPlayer(Match);            
              if (LocalPlayer) 
              {
                   void* closestEnemy = GetClosestEnemy(Match);				
	               if (closestEnemy) 
	               {
	                    Vector3 EnemyVehicleLocation = GetHeadPosition(closestEnemy);
                        if (Vehicle.TeleportCar)
                        {
                             void* LocalVehicle = Tele_LocalVehicle(LocalPlayer);
                             if (LocalVehicle) 
                             {
                                   Transform_INTERNAL_SetPosition(Component_GetTransform(LocalVehicle), Vvector3(EnemyVehicleLocation.X, EnemyVehicleLocation.Y, EnemyVehicleLocation.Z));
                             }
                        }
                   }
	          }
	     }
    }
    orig_LateUpdateVehicle(player);
}


/* -------------------- > Update LateUpdateVehicle < -------------------- */
    
    devilydevily("libil2cpp.so", "0xC25F18", hook_LateUpdateVehicle, orig_LateUpdateVehicle); //[1.80]