using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Cyanide
{
    public class MapName
    {
        public MapName(string map, string name)
        {
            Map = map;
            Name = name;
        }
        public string Map;
        public string Name;
    }
    public class Position
    {
        public Position(decimal x, decimal y, decimal z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        public decimal X;
        public decimal Y;
        public decimal Z;
    }
    public class Rotation
    {
        public Rotation(decimal u, decimal v, decimal w)
        {
            U = u;
            V = v;
            W = w;
        }
        public decimal U;
        public decimal V;
        public decimal W;
    }
    public class PositionUpdatedEventArgs
    {
        public PositionUpdatedEventArgs(Position p, Rotation r)
        {
            position = p;
            rotation = r;
        }
        public Position position { get; private set; }
        public Rotation rotation { get; private set; }
    }
    class PlayerData
    {
        public delegate void PositionUpdatedEventHandler(object sender, PositionUpdatedEventArgs e);
        public event PositionUpdatedEventHandler PositionUpdated;

        public Position position = new Position(0, 0, 0);
        public Rotation rotation = new Rotation(0, 0, 0);
        public MapName CurrentMap = null;

        private string cMap = string.Empty;
        private List<MapName> colMaps = new List<MapName> ();

        #region Constructors
        public PlayerData()
        {
            colMaps.Add(new MapName("maps/game_start.b", "Start Screen"));
            colMaps.Add(new MapName("maps/t01.b", "Colhen"));
            colMaps.Add(new MapName("maps/t02.b", "Rocheste"));
            colMaps.Add(new MapName("maps/f01.b", "Fields"));
            colMaps.Add(new MapName("", ""));
        }
        #endregion

        #region Properties
        public string map
        {
            get { return cMap; }
            set
            {
                cMap = value;
                foreach (MapName m in colMaps)
                {
                    if (m.Map == cMap)
                    {
                        CurrentMap = m;
                    }
                }
            }
        }
        #endregion

        #region Methods
        public void PositionChanged()
        {
            PositionUpdated(this, new PositionUpdatedEventArgs(position, rotation));
        }
        #endregion
    }
}
